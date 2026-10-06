// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ISlateStyle;

class FScooterUtilsStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle &Get();
	static FName GetStyleSetName();
};
