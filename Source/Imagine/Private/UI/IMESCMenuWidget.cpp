// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMESCMenuWidget.h"
#include"UI/IMBaseHUD.h"
#include"Components/Button.h"
#include"Kismet/GameplayStatics.h"
#include"Debug/MyDebug.h"
UIMESCMenuWidget::UIMESCMenuWidget(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	
}

void UIMESCMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BackToMenu->OnClicked.AddDynamic(this, &UIMESCMenuWidget::BackToMainMenu_Pre);
}

void UIMESCMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MyHUD = nullptr;
	bHavPendingBacking = false;
}

FReply UIMESCMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (bHavPendingBacking) return FReply::Handled();
	FKey TheKey = InKeyEvent.GetKey();
	if (TheKey == EKeys::Escape) {
		GetMyHUD()->ESCMenu_Close();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

AIMBaseHUD* UIMESCMenuWidget::GetMyHUD()
{
	if (!MyHUD) {
		check(GetOwningPlayer());
		MyHUD = Cast<AIMBaseHUD>(GetOwningPlayer()->GetHUD());
		check(MyHUD);
	}
	return MyHUD;
}

void UIMESCMenuWidget::BackToMainMenu_Pre()
{
	if (bHavPendingBacking) return;
	bHavPendingBacking = true;
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMESCMenuWidget::BackToMainMenu,0.8);
}

void UIMESCMenuWidget::BackToMainMenu()
{
	GetMyHUD()->ESCMenu_Close();
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}
