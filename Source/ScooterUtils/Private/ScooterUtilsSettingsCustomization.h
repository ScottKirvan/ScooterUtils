// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#pragma once

#include "IDetailCustomization.h"

class FScooterUtilsSettingsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder &DetailBuilder) override;
};
