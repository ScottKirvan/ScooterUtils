// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsSettingsCustomization.h"
#include "ScooterUtilsAboutDialog.h"
#include "ScooterUtilsSettings.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"

#define LOCTEXT_NAMESPACE "ScooterUtilsSettingsCustomization"

TSharedRef<IDetailCustomization> FScooterUtilsSettingsCustomization::MakeInstance()
{
	return MakeShared<FScooterUtilsSettingsCustomization>();
}

void FScooterUtilsSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder &DetailBuilder)
{
	IDetailCategoryBuilder &AboutCategory = DetailBuilder.EditCategory("About Scooter Utilities");

	AboutCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ScooterUtilsVersion)));
	AboutCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ScooterUtilsCopyright)));

	AboutCategory.AddCustomRow(LOCTEXT("AboutRowFilter", "About ScooterUtils"))
		.WholeRowContent()
			[SNew(SBox)
				 .HAlign(HAlign_Left)
					 [SNew(SButton)
						  .Text(LOCTEXT("AboutButton", "About ScooterUtils..."))
						  .ToolTipText(LOCTEXT("AboutButtonTooltip", "Show version, build information, and links for Scooter Utilities"))
						  .OnClicked_Lambda([]()
											{
							ScooterUtilsAbout::Show();
							return FReply::Handled(); })]];
}

#undef LOCTEXT_NAMESPACE
