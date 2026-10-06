// Copyright (c) 2020-2026 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsAboutDialog.h"
#include "ScooterUtilsBuildInfo.h"
#include "ScooterUtilsStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "HAL/PlatformProcess.h"
#include "InputCoreTypes.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/AppStyle.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "ScooterUtilsAbout"

namespace
{
	struct FAboutLink
	{
		FName IconBrush;
		FText Title;
		FText Description;
		FText ButtonLabel;
		FString Url;
		bool bPrimary;
	};

	TArray<FAboutLink> GetAboutLinks()
	{
		return {
			{TEXT("ScooterUtils.Docs"), LOCTEXT("DocsTitle", "Documentation"), LOCTEXT("DocsDescription", "Official guide and setup instructions."), LOCTEXT("DocsButton", "Visit"), TEXT("https://www.scottkirvan.com/ScooterUtils/"), true},
			{TEXT("ScooterUtils.Discord"), LOCTEXT("DiscordTitle", "Discord"), LOCTEXT("DiscordDescription", "Chat with other ScooterUtils users and get support."), LOCTEXT("DiscordButton", "Join"), TEXT("https://discord.gg/TN6XJSNK5Y"), false},
			{TEXT("ScooterUtils.GitHub"), LOCTEXT("GitHubTitle", "GitHub"), LOCTEXT("GitHubDescription", "Source code, issues, and release notes."), LOCTEXT("GitHubButton", "View"), TEXT("https://github.com/ScottKirvan/ScooterUtils"), false},
			{TEXT("ScooterUtils.Kofi"), LOCTEXT("KofiTitle", "Buy me a coffee"), LOCTEXT("KofiDescription", "Show your love. Support ScooterUtils and the author."), LOCTEXT("KofiButton", "Give"), TEXT("https://ko-fi.com/ScottKirvan"), false},
		};
	}
}

class SScooterUtilsAboutDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SScooterUtilsAboutDialog) {}
	SLATE_EVENT(FSimpleDelegate, OnClose)
	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs)
	{
		OnClose = InArgs._OnClose;

		TSharedRef<SVerticalBox> Rows = SNew(SVerticalBox);
		for (const FAboutLink &Link : GetAboutLinks())
		{
			Rows->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 6.0f)
				[MakeLinkRow(Link)];
		}

		ChildSlot
			[SNew(SBox)
				 .WidthOverride(420.0f)
					 [SNew(SBorder)
						  .BorderImage(FAppStyle::GetBrush("Brushes.Panel"))
						  .Padding(FMargin(24.0f, 20.0f))
							  [SNew(SVerticalBox)
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .HAlign(HAlign_Center)
										 [SNew(SImage)
											  .Image(FScooterUtilsStyle::Get().GetBrush("ScooterUtils.Logo"))]
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .HAlign(HAlign_Center)
									 .Padding(0.0f, 12.0f, 0.0f, 0.0f)
										 [SNew(STextBlock)
											  .Text(LOCTEXT("ProductName", "ScooterUtils"))
											  .Font(FCoreStyle::GetDefaultFontStyle("Bold", 16))]
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .HAlign(HAlign_Center)
									 .Padding(0.0f, 8.0f, 0.0f, 0.0f)
										 [SNew(STextBlock)
											  .Text(ScooterUtilsBuildInfo::GetVersionHeading())]
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .HAlign(HAlign_Center)
									 .Padding(0.0f, 2.0f, 0.0f, 0.0f)
										 [SNew(STextBlock)
											  .Text(FText::FromString(ScooterUtilsBuildInfo::GetBuildLine()))
											  .TextStyle(FAppStyle::Get(), "SmallText")
											  .ColorAndOpacity(FSlateColor::UseSubduedForeground())]
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .Padding(0.0f, 16.0f, 0.0f, 8.0f)
										 [SNew(SSeparator)
											  .Orientation(Orient_Horizontal)]
							   + SVerticalBox::Slot()
									 .AutoHeight()
										 [Rows]
							   + SVerticalBox::Slot()
									 .AutoHeight()
									 .HAlign(HAlign_Right)
									 .Padding(0.0f, 16.0f, 0.0f, 0.0f)
										 [SNew(SButton)
											  .Text(LOCTEXT("Close", "Close"))
											  .OnClicked(this, &SScooterUtilsAboutDialog::HandleClose)]]]];
	}

	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnKeyDown(const FGeometry &MyGeometry, const FKeyEvent &InKeyEvent) override
	{
		if (InKeyEvent.GetKey() == EKeys::Escape)
		{
			return HandleClose();
		}
		return SCompoundWidget::OnKeyDown(MyGeometry, InKeyEvent);
	}

private:
	TSharedRef<SWidget> MakeLinkRow(const FAboutLink &Link)
	{
		const FButtonStyle *ButtonStyle = Link.bPrimary
			? &FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton.Success")
			: &FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
		const FName TextStyle = Link.bPrimary ? FName("FlatButton.DefaultTextStyle") : FName("ButtonText");
		const FString Url = Link.Url;

		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(0.0f, 0.0f, 14.0f, 0.0f)
					  [SNew(SImage)
						   .Image(FScooterUtilsStyle::Get().GetBrush(Link.IconBrush))
						   .ColorAndOpacity(FSlateColor::UseForeground())]
			+ SHorizontalBox::Slot()
				  .FillWidth(1.0f)
				  .VAlign(VAlign_Center)
					  [SNew(SVerticalBox)
					   + SVerticalBox::Slot()
							 .AutoHeight()
								 [SNew(STextBlock)
									  .Text(Link.Title)
									  .Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))]
					   + SVerticalBox::Slot()
							 .AutoHeight()
								 [SNew(STextBlock)
									  .Text(Link.Description)
									  .TextStyle(FAppStyle::Get(), "SmallText")
									  .ColorAndOpacity(FSlateColor::UseSubduedForeground())
									  .AutoWrapText(true)]]
			+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(12.0f, 0.0f, 0.0f, 0.0f)
					  [SNew(SBox)
						   .WidthOverride(72.0f)
							   [SNew(SButton)
									.ButtonStyle(ButtonStyle)
									.TextStyle(FAppStyle::Get(), TextStyle)
									.HAlign(HAlign_Center)
									.Text(Link.ButtonLabel)
									.ToolTipText(FText::FromString(Url))
									.OnClicked_Lambda([Url]()
													  {
								FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
								return FReply::Handled(); })]];
	}

	FReply HandleClose()
	{
		OnClose.ExecuteIfBound();
		return FReply::Handled();
	}

	FSimpleDelegate OnClose;
};

void ScooterUtilsAbout::Show()
{
	if (!FSlateApplication::IsInitialized() || !IPluginManager::Get().FindPlugin(TEXT("ScooterUtils")).IsValid())
	{
		return;
	}

	TSharedPtr<SWindow> Window;
	TSharedPtr<SScooterUtilsAboutDialog> Dialog;

	Window = SNew(SWindow)
				 .Title(LOCTEXT("WindowTitle", "About ScooterUtils"))
				 .SizingRule(ESizingRule::Autosized)
				 .AutoCenter(EAutoCenter::PreferredWorkArea)
				 .SupportsMaximize(false)
				 .SupportsMinimize(false);

	TWeakPtr<SWindow> WeakWindow = Window;
	Dialog = SNew(SScooterUtilsAboutDialog)
				 .OnClose(FSimpleDelegate::CreateLambda([WeakWindow]()
														{
					if (TSharedPtr<SWindow> PinnedWindow = WeakWindow.Pin())
					{
						PinnedWindow->RequestDestroyWindow();
					} }));

	Window->SetContent(Dialog.ToSharedRef());
	Window->SetWidgetToFocusOnActivate(Dialog);

	FSlateApplication::Get().AddModalWindow(Window.ToSharedRef(), FGlobalTabmanager::Get()->GetRootWindow());
}

#undef LOCTEXT_NAMESPACE
