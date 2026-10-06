// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScooterUtilsBPLibrary.h"
#include "HAL/FileManager.h"
#include "CoreGlobals.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Runtime/Launch/Resources/Version.h"
#include <type_traits>

UScooterUtilsBPLibrary::UScooterUtilsBPLibrary(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

namespace
{
	bool ResolveConfigFilename(EGlobalConfigScope Scope, FString &OutFilename, FString &OutReason)
	{
		OutFilename.Reset();
		OutReason.Reset();

		if (GConfig == nullptr)
		{
			OutReason = TEXT("The Unreal config cache is unavailable.");
			return false;
		}

		switch (Scope)
		{
		case EGlobalConfigScope::Project:
			OutFilename = GEditorIni;
			break;
		case EGlobalConfigScope::UserGlobal:
			OutFilename = GEditorSettingsIni;
			if (OutFilename.IsEmpty())
			{
				OutReason = TEXT("User Global config is only available when the editor settings file is initialized.");
				return false;
			}
			break;
		default:
			OutReason = TEXT("The selected config scope is invalid.");
			return false;
		}

		if (OutFilename.IsEmpty() || GConfig->Find(*OutFilename) == nullptr)
		{
			OutReason = FString::Printf(TEXT("The config file for the selected scope is unavailable: %s"), *OutFilename);
			return false;
		}

		return true;
	}
}

namespace
{
	template <typename TValue, typename Getter>
	TValue ReadGlobalConfigValue(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		EGlobalConfigScope &OutScope,
		EGlobalConfigResult &OutResult,
		FString &OutReason,
		Getter &&GetValue)
	{
		OutSection = Section;
		OutKey = Key;
		OutScope = Scope;
		OutResult = EGlobalConfigResult::Success;
		OutReason.Reset();

		TValue Value{};
		if (Section.TrimStartAndEnd().IsEmpty() || Key.TrimStartAndEnd().IsEmpty())
		{
			OutResult = EGlobalConfigResult::InvalidInput;
			OutReason = TEXT("Section and Key must both contain non-whitespace characters.");
			return Value;
		}

		FString ConfigFilename;
		if (!ResolveConfigFilename(Scope, ConfigFilename, OutReason))
		{
			OutResult = (Scope == EGlobalConfigScope::Project || Scope == EGlobalConfigScope::UserGlobal)
							? EGlobalConfigResult::ConfigUnavailable
							: EGlobalConfigResult::InvalidInput;
			return Value;
		}

		if (!GetValue(Value, ConfigFilename))
		{
			OutResult = EGlobalConfigResult::KeyNotFound;
			OutReason = FString::Printf(TEXT("Key '%s' was not found in section '%s' for the selected scope."), *Key, *Section);
		}

		return Value;
	}

	// FConfigCacheIni::Flush returns void before UE 5.8 and bool from 5.8 on.
	template <typename TConfigCache>
	bool FlushConfigCache(TConfigCache &Cache, const FString &ConfigFilename)
	{
		if constexpr (std::is_void_v<decltype(Cache.Flush(false, ConfigFilename))>)
		{
			Cache.Flush(false, ConfigFilename);
			return true;
		}
		else
		{
			return Cache.Flush(false, ConfigFilename);
		}
	}

	template <typename Writer, typename DiskVerifier>
	EGlobalConfigResult WriteGlobalConfigValue(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutReason,
		Writer &&WriteValue,
		DiskVerifier &&VerifyDiskValue)
	{
		OutReason.Reset();
		if (Section.TrimStartAndEnd().IsEmpty() || Key.TrimStartAndEnd().IsEmpty())
		{
			OutReason = TEXT("Section and Key must both contain non-whitespace characters.");
			return EGlobalConfigResult::InvalidInput;
		}

		FString ConfigFilename;
		if (!ResolveConfigFilename(Scope, ConfigFilename, OutReason))
		{
			return (Scope == EGlobalConfigScope::Project || Scope == EGlobalConfigScope::UserGlobal)
					   ? EGlobalConfigResult::ConfigUnavailable
					   : EGlobalConfigResult::InvalidInput;
		}

		FString SavePath;
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
		// UE 5.5+ stores configs in FConfigBranch objects.
		FConfigBranch *ConfigBranch = GConfig->FindBranch(FName(*ConfigFilename), ConfigFilename);
		if (ConfigBranch != nullptr)
		{
			SavePath = ConfigBranch->IniPath;
		}
#else
		// Before UE 5.5 the cache is keyed by the ini path itself.
		if (GConfig->FindConfigFile(ConfigFilename) != nullptr)
		{
			SavePath = ConfigFilename;
		}
#endif
		if (SavePath.IsEmpty())
		{
			OutReason = FString::Printf(TEXT("Could not resolve the save path for config '%s'."), *ConfigFilename);
			return EGlobalConfigResult::ConfigUnavailable;
		}

		WriteValue(ConfigFilename);

		if (Scope == EGlobalConfigScope::Project)
		{
			// Unreal regenerates Saved/Config/<Platform>/Editor.ini and drops custom sections,
			// so project values persist in the project's DefaultEditor.ini instead.
			SavePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir() / TEXT("DefaultEditor.ini"));

			FString StringValue;
			if (!GConfig->GetString(*Section, *Key, StringValue, ConfigFilename))
			{
				OutReason = TEXT("The value could not be read back from the in-memory config.");
				return EGlobalConfigResult::SaveFailed;
			}

			if (IFileManager::Get().FileExists(*SavePath) && IFileManager::Get().IsReadOnly(*SavePath))
			{
				OutReason = FString::Printf(TEXT("DefaultEditor.ini is read-only (check it out of source control first): %s"), *SavePath);
				return EGlobalConfigResult::SaveFailed;
			}

			FConfigFile DefaultConfig;
			DefaultConfig.Read(SavePath);
			DefaultConfig.SetString(*Section, *Key, *StringValue);
			if (!DefaultConfig.Write(SavePath))
			{
				OutReason = FString::Printf(TEXT("Unreal failed to write DefaultEditor.ini: %s"), *SavePath);
				return EGlobalConfigResult::SaveFailed;
			}
		}
		else if (!FlushConfigCache(*GConfig, ConfigFilename))
		{
			OutReason = FString::Printf(TEXT("Unreal failed to flush the selected config file: %s"), *SavePath);
			return EGlobalConfigResult::SaveFailed;
		}

		if (!IFileManager::Get().FileExists(*SavePath))
		{
			OutReason = FString::Printf(TEXT("Unreal did not create the selected config file: %s"), *SavePath);
			return EGlobalConfigResult::SaveFailed;
		}

		FConfigFile SavedConfig;
		FString SavedFileContents;
		if (!FFileHelper::LoadFileToString(SavedFileContents, *SavePath))
		{
			OutReason = FString::Printf(TEXT("Could not read the saved config file for verification: %s"), *SavePath);
			return EGlobalConfigResult::SaveFailed;
		}
		SavedConfig.Read(SavePath);
		if (!VerifyDiskValue(SavedConfig))
		{
			OutReason = FString::Printf(TEXT("The value was not present in the saved config file: %s"), *SavePath);
			return EGlobalConfigResult::SaveFailed;
		}

		return EGlobalConfigResult::Success;
	}
}

FString UScooterUtilsBPLibrary::GetGlobalConfigFileString(
	const FString &Section, const FString &Key, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, EGlobalConfigScope &OutScope,
	EGlobalConfigResult &OutResult, FString &OutReason)
{
	return ReadGlobalConfigValue<FString>(Section, Key, Scope, OutSection, OutKey, OutScope, OutResult, OutReason,
		[&Section, &Key](FString &Value, const FString &ConfigFilename)
		{
			return GConfig->GetString(*Section, *Key, Value, ConfigFilename);
		});
}

float UScooterUtilsBPLibrary::GetGlobalConfigFileFloat(
	const FString &Section, const FString &Key, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, EGlobalConfigScope &OutScope,
	EGlobalConfigResult &OutResult, FString &OutReason)
{
	return ReadGlobalConfigValue<float>(Section, Key, Scope, OutSection, OutKey, OutScope, OutResult, OutReason,
		[&Section, &Key](float &Value, const FString &ConfigFilename)
		{
			return GConfig->GetFloat(*Section, *Key, Value, ConfigFilename);
		});
}

bool UScooterUtilsBPLibrary::GetGlobalConfigFileBool(
	const FString &Section, const FString &Key, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, EGlobalConfigScope &OutScope,
	EGlobalConfigResult &OutResult, FString &OutReason)
{
	return ReadGlobalConfigValue<bool>(Section, Key, Scope, OutSection, OutKey, OutScope, OutResult, OutReason,
		[&Section, &Key](bool &Value, const FString &ConfigFilename)
		{
			return GConfig->GetBool(*Section, *Key, Value, ConfigFilename);
		});
}

int32 UScooterUtilsBPLibrary::GetGlobalConfigFileInt(
	const FString &Section, const FString &Key, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, EGlobalConfigScope &OutScope,
	EGlobalConfigResult &OutResult, FString &OutReason)
{
	return ReadGlobalConfigValue<int32>(Section, Key, Scope, OutSection, OutKey, OutScope, OutResult, OutReason,
		[&Section, &Key](int32 &Value, const FString &ConfigFilename)
		{
			return GConfig->GetInt(*Section, *Key, Value, ConfigFilename);
		});
}

EGlobalConfigResult UScooterUtilsBPLibrary::SetGlobalConfigFileString(
	const FString &Section, const FString &Key, const FString &Value, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, FString &OutValue, EGlobalConfigScope &OutScope,
	FString &OutReason)
{
	OutSection = Section;
	OutKey = Key;
	OutValue = Value;
	OutScope = Scope;
	return WriteGlobalConfigValue(Section, Key, Scope, OutReason,
		[&Section, &Key, &Value](const FString &ConfigFilename)
		{
			GConfig->SetString(*Section, *Key, *Value, ConfigFilename);
		},
		[&Section, &Key, &Value](const FConfigFile &SavedConfig)
		{
			FString SavedValue;
			return SavedConfig.GetString(*Section, *Key, SavedValue) && SavedValue == Value;
		});
}

EGlobalConfigResult UScooterUtilsBPLibrary::SetGlobalConfigFileFloat(
	const FString &Section, const FString &Key, float Value, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, float &OutValue, EGlobalConfigScope &OutScope,
	FString &OutReason)
{
	OutSection = Section;
	OutKey = Key;
	OutValue = Value;
	OutScope = Scope;
	return WriteGlobalConfigValue(Section, Key, Scope, OutReason,
		[&Section, &Key, Value](const FString &ConfigFilename)
		{
			GConfig->SetFloat(*Section, *Key, Value, ConfigFilename);
		},
		[&Section, &Key, Value](const FConfigFile &SavedConfig)
		{
			float SavedValue = 0.0f;
			return SavedConfig.GetFloat(*Section, *Key, SavedValue) && FMath::IsNearlyEqual(SavedValue, Value);
		});
}

EGlobalConfigResult UScooterUtilsBPLibrary::SetGlobalConfigFileBool(
	const FString &Section, const FString &Key, bool Value, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, bool &OutValue, EGlobalConfigScope &OutScope,
	FString &OutReason)
{
	OutSection = Section;
	OutKey = Key;
	OutValue = Value;
	OutScope = Scope;
	return WriteGlobalConfigValue(Section, Key, Scope, OutReason,
		[&Section, &Key, Value](const FString &ConfigFilename)
		{
			GConfig->SetBool(*Section, *Key, Value, ConfigFilename);
		},
		[&Section, &Key, Value](const FConfigFile &SavedConfig)
		{
			bool SavedValue = false;
			return SavedConfig.GetBool(*Section, *Key, SavedValue) && SavedValue == Value;
		});
}

EGlobalConfigResult UScooterUtilsBPLibrary::SetGlobalConfigFileInt(
	const FString &Section, const FString &Key, int32 Value, EGlobalConfigScope Scope,
	FString &OutSection, FString &OutKey, int32 &OutValue, EGlobalConfigScope &OutScope,
	FString &OutReason)
{
	OutSection = Section;
	OutKey = Key;
	OutValue = Value;
	OutScope = Scope;
	return WriteGlobalConfigValue(Section, Key, Scope, OutReason,
		[&Section, &Key, Value](const FString &ConfigFilename)
		{
			GConfig->SetInt(*Section, *Key, Value, ConfigFilename);
		},
		[&Section, &Key, Value](const FConfigFile &SavedConfig)
		{
			int32 SavedValue = 0;
			return SavedConfig.GetInt(*Section, *Key, SavedValue) && SavedValue == Value;
		});
}
