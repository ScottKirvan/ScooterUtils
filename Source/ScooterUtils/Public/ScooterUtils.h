// Copyright (c) 2020-2025 Scott Kirvan. All Rights Reserved.

#pragma once

#include "Toolkits/AssetEditorToolkit.h"

DECLARE_LOG_CATEGORY_EXTERN(LogScooterUtils, Log, All);

class IScooterUtilsModuleListenerInterface
{
public:
	virtual ~IScooterUtilsModuleListenerInterface() {};

	virtual void OnStartupModule() {};
	virtual void OnShutdownModule() {};
};

class FScooterUtilsModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners();

	static inline FScooterUtilsModule &Get()
	{
		return FModuleManager::LoadModuleChecked<FScooterUtilsModule>("ScooterUtils");
	}

	void AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList = nullptr, EExtensionHook::Position position = EExtensionHook::After);

	void EditorIsFullyLoaded() const;
	FDelegateHandle MyHandle;

protected:
	TArray<TSharedRef<IScooterUtilsModuleListenerInterface>> ModuleListeners;
	TSharedPtr<FExtender> MenuExtender;

	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;

private:
	static void ShowViewportFPS();
};
