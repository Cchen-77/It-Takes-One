// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMESCMenuWidget.h"
#include"UI/IMBaseHUD.h"
#include"Components/Button.h"
#include"Kismet/GameplayStatics.h"
#include"Debug/MyDebug.h"
#include"Kismet/GameplayStatics.h"
#include"Kismet/KismetSystemLibrary.h"
UIMESCMenuWidget::UIMESCMenuWidget(const FObjectInitializer& ObjInit)
{
	
}

void UIMESCMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Resume->OnClicked.AddDynamic(GetMyHUD(), &AIMBaseHUD::ESCMenu_Close);
	BackToMenu->OnClicked.AddDynamic(this, &UIMESCMenuWidget::BackToMainMenu_Pre);
	RestartCurrent->OnClicked.AddDynamic(this, &UIMESCMenuWidget::Restart_Pre);
}

void UIMESCMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bHavPendingBacking = false;
}

FReply UIMESCMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (!CanbeOperating()) return FReply::Handled();
	FKey TheKey = InKeyEvent.GetKey();
	if (TheKey == EKeys::Escape) {
		GetMyHUD()->ESCMenu_Close();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UIMESCMenuWidget::BackToMainMenu_Pre()
{
	if (!CanbeOperating()) return;
	bHavPendingBacking = true;
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMESCMenuWidget::BackToMainMenu,0.8);
}

void UIMESCMenuWidget::BackToMainMenu()
{
	GetMyHUD()->ESCMenu_Close();
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void UIMESCMenuWidget::Restart_Pre()
{
	if (!CanbeOperating()) return;
	bHavPendingRestarting = true;
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMESCMenuWidget::Restart, 0.8);
}

void UIMESCMenuWidget::Restart()
{
	GetMyHUD()->ESCMenu_Close();
	UMyDebug::Message(GetWorld()->GetName());
	UGameplayStatics::OpenLevel(GetWorld(),FName(*GetWorld()->GetName()));
}

bool UIMESCMenuWidget::CanbeOperating() const
{
	return !(bHavPendingBacking || bHavPendingRestarting);
}
