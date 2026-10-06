// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateImageBrush.h"

namespace
{
	TSharedPtr<FSlateStyleSet> StyleInstance;
}

void FScooterUtilsStyle::Initialize()
{
	if (StyleInstance.IsValid())
	{
		return;
	}

	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ScooterUtils"));
	if (!Plugin.IsValid())
	{
		return;
	}

	StyleInstance = MakeShared<FSlateStyleSet>(GetStyleSetName());
	StyleInstance->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	const FVector2D LogoSize(80.0f, 80.0f);
	const FVector2D RowIconSize(24.0f, 24.0f);

	StyleInstance->Set("ScooterUtils.Logo", new FSlateImageBrush(StyleInstance->RootToContentDir(TEXT("Icon128"), TEXT(".png")), LogoSize));
	StyleInstance->Set("ScooterUtils.Docs", new FSlateVectorImageBrush(StyleInstance->RootToContentDir(TEXT("Icons/Docs"), TEXT(".svg")), RowIconSize));
	StyleInstance->Set("ScooterUtils.Discord", new FSlateVectorImageBrush(StyleInstance->RootToContentDir(TEXT("Icons/Discord"), TEXT(".svg")), RowIconSize));
	StyleInstance->Set("ScooterUtils.GitHub", new FSlateVectorImageBrush(StyleInstance->RootToContentDir(TEXT("Icons/GitHub"), TEXT(".svg")), RowIconSize));
	StyleInstance->Set("ScooterUtils.Kofi", new FSlateVectorImageBrush(StyleInstance->RootToContentDir(TEXT("Icons/Kofi"), TEXT(".svg")), RowIconSize));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FScooterUtilsStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}

const ISlateStyle &FScooterUtilsStyle::Get()
{
	return *StyleInstance;
}

FName FScooterUtilsStyle::GetStyleSetName()
{
	return TEXT("ScooterUtilsStyle");
}
