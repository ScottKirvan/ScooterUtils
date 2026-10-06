// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsBuildInfo.h"
#include "ScooterUtilsVersion.h"
#include "ScooterUtilsBuildInfo.generated.h"

#define LOCTEXT_NAMESPACE "ScooterUtilsBuildInfo"

namespace ScooterUtilsBuildInfo
{
	FString GetVersionLabel()
	{
		return FString::Printf(TEXT("v%d.%d.%d"), SCOOTER_UTILS_VERSION_MAJOR, SCOOTER_UTILS_VERSION_MINOR, SCOOTER_UTILS_VERSION_PATCH);
	}

	FText GetVersionHeading()
	{
		return FText::Format(LOCTEXT("VersionHeading", "Version {0}.{1}.{2}"),
							 SCOOTER_UTILS_VERSION_MAJOR, SCOOTER_UTILS_VERSION_MINOR, SCOOTER_UTILS_VERSION_PATCH);
	}

	FString FormatBuildLine(const FString &Branch, const FString &Version, const FString &BuiltAtUtc)
	{
		const bool bShowVersion = Branch.IsEmpty() || Branch.Equals(TEXT("main"), ESearchCase::CaseSensitive);
		return FString::Printf(TEXT("%s \u00B7 %s UTC"), bShowVersion ? *Version : *Branch, *BuiltAtUtc);
	}

	FString GetBuildLine()
	{
		return FormatBuildLine(SCOOTER_UTILS_BUILD_BRANCH, GetVersionLabel(), SCOOTER_UTILS_BUILD_TIME_UTC);
	}
}

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScooterUtilsBuildLineTest, "ScooterUtils.BuildInfo.FormatBuildLine",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FScooterUtilsBuildLineTest::RunTest(const FString &Parameters)
{
	using namespace ScooterUtilsBuildInfo;
	const FString Version = TEXT("v1.2.3");
	const FString Time = TEXT("2026-10-04 00:05");

	TestEqual(TEXT("main build shows the version"), FormatBuildLine(TEXT("main"), Version, Time), TEXT("v1.2.3 \u00B7 2026-10-04 00:05 UTC"));
	TestEqual(TEXT("unknown branch shows the version"), FormatBuildLine(TEXT(""), Version, Time), TEXT("v1.2.3 \u00B7 2026-10-04 00:05 UTC"));
	TestEqual(TEXT("feature branch shows the branch name"), FormatBuildLine(TEXT("feat/about-dialog"), Version, Time), TEXT("feat/about-dialog \u00B7 2026-10-04 00:05 UTC"));
	TestEqual(TEXT("branch named like main is not main"), FormatBuildLine(TEXT("Main"), Version, Time), TEXT("Main \u00B7 2026-10-04 00:05 UTC"));
	return true;
}

#endif

#undef LOCTEXT_NAMESPACE
