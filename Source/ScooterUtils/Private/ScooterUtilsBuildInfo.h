// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace ScooterUtilsBuildInfo
{
	/** "v1.2.3" from the release-managed version header. */
	FString GetVersionLabel();

	/** "Version 1.2.3" for the About dialog heading. */
	FText GetVersionHeading();

	/**
	 * "<version or branch> · <yyyy-MM-dd HH:mm> UTC". Builds from main (or with no known branch) show the version,
	 * every other build shows its branch name.
	 */
	FString FormatBuildLine(const FString &Branch, const FString &Version, const FString &BuiltAtUtc);

	FString GetBuildLine();
}
