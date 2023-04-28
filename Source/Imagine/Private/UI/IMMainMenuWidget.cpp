// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMMainMenuWidget.h"
#include"UI/IMBaseHUD.h"
#include"Debug/MyDebug.h"
UIMMainMenuWidget::UIMMainMenuWidget(const FObjectInitializer& ObjInit)
{
	bIsFocusable = true;
}

void UIMMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(StartBlink, 0, 0);
}

FReply UIMMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	FKey TheKey = InKeyEvent.GetKey();
	if (TheKey == EKeys::SpaceBar) {
		GetMyHUD()->LevelSelecting_Open();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
