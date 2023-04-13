// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMBaseHUD.h"
#include"UI/IMMainMenuWidget.h"
#include"UI/IMTransitionWidget.h"
#include"UI/IMLevelSelectingWidget.h"
#include"UI/IMESCMenuWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"Debug/MyDebug.h"
void AIMBaseHUD::Transition_Fadein()
{
	if (TransitionWidget) {
		TransitionWidget->Fadein();
	}
}
void AIMBaseHUD::Transition_Fadeout()
{
	if (!TransitionWidget) {
		check(TransitionWidgetClass);
		TransitionWidget = CreateWidget<UIMTransitionWidget>(GetOwningPlayerController(), TransitionWidgetClass);
	}
	TransitionWidget->AddToViewport(10);
	TransitionWidget->FadeOut();
}

void AIMBaseHUD::MainMenu_Open()
{
	if (HUDMode != EHUDMode::MODE_MAINMENU) {
		return;
	}
	if (!MainMenuWidget) {
		check(MainMenuWidgetClass);
		MainMenuWidget = CreateWidget<UIMMainMenuWidget>(GetOwningPlayerController(), MainMenuWidgetClass);
	}
	MainMenuWidget->AddToViewport();
}

void AIMBaseHUD::LevelSelecting_Open()
{
	if (HUDMode != EHUDMode::MODE_MAINMENU) {
		return;
	}
	if (!LevelSelectingWidget) {
		check(LevelSelectingWidgetClass);
		LevelSelectingWidget = CreateWidget<UIMLevelSelectingWidget>(GetOwningPlayerController(), LevelSelectingWidgetClass);
	}
	LevelSelectingWidget->AddToViewport();
	LevelSelectingWidget->SetFocus();
}

void AIMBaseHUD::LevelSelecting_Close()
{
	if (HUDMode != EHUDMode::MODE_MAINMENU) {
		return;
	}
	if (LevelSelectingWidget) {
		LevelSelectingWidget->RemoveFromParent();
		if (MainMenuWidget) {
			MainMenuWidget->SetFocus();
		}
	}
}

void AIMBaseHUD::ESCMenu_Open()
{
	if (HUDMode != EHUDMode::MODE_GAMEPLAY) {
		return;
	}
	if (!ESCMenuWidget) {
		check(ESCMenuWidgetClass);
		ESCMenuWidget = CreateWidget<UIMESCMenuWidget>(GetOwningPlayerController(), ESCMenuWidgetClass);
	}
	ESCMenuWidget->AddToViewport();
	SetInputModeUIOnly(ESCMenuWidget);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
void AIMBaseHUD::ESCMenu_Close()
{
	if (HUDMode != EHUDMode::MODE_GAMEPLAY) {
		return;
	}
	if (ESCMenuWidget) {
		ESCMenuWidget->RemoveFromViewport();
		SetInputModeGameplayOnly();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AIMBaseHUD::BeginPlay()
{
	Super::BeginPlay();
	Transition_Fadeout();
	if (HUDMode == EHUDMode::MODE_MAINMENU) {
		MainMenu_Open();
		SetInputModeUIOnly(MainMenuWidget);
	}
	if (HUDMode == EHUDMode::MODE_GAMEPLAY) {
		SetInputModeGameplayOnly();
	}
}

void AIMBaseHUD::SetInputModeUIOnly(UUserWidget* FocusWidget)
{
	auto PC = GetOwningPlayerController();
	check(PC);
	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
	FocusWidget->SetFocus();
}

void AIMBaseHUD::SetInputModeGameplayOnly()
{
	auto PC = GetOwningPlayerController();
	check(PC);
	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}
