// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMLevelFinishWidget.h"
#include"UI/IMBaseHUD.h"
#include"IMBaseGameInstance.h"
#include"Kismet/GameplayStatics.h"
#include"Components/Button.h"
#include"Animation/WidgetAnimation.h"
void UIMLevelFinishWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Next->OnClicked.AddDynamic(this, &UIMLevelFinishWidget::NextLevel_Pre);
	MainMenu->OnClicked.AddDynamic(this, &UIMLevelFinishWidget::BackToMenu_Pre);
}

void UIMLevelFinishWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bInFadeingIn = false;
	bHavPendingNextLevel = false;
	bHavPendingBacking = false;
	GetWorld()->GetTimerManager().SetTimer(Fadingin_Timer, this, &UIMLevelFinishWidget::OnFadinginFinish, 0.5);
	PlayAnimation(FadeinAnim);
}

void UIMLevelFinishWidget::NextLevel_Pre()
{
	if (!CanbeOperating()) return;
	bHavPendingNextLevel = true;
	auto GI = GetMyGI();
	NextLevelNameCache = GI->GetNextLevelName();
	if (NextLevelNameCache == "NULL") {
		bHavPendingNextLevel = false;
		return;
	}
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMLevelFinishWidget::NextLevel, 0.8);
}

void UIMLevelFinishWidget::NextLevel()
{
	
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelNameCache, false);
}

void UIMLevelFinishWidget::OnFadinginFinish()
{
	bInFadeingIn = false;
}

void UIMLevelFinishWidget::BackToMenu_Pre()
{
	if (!CanbeOperating()) return;
	bHavPendingBacking = true;
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMLevelFinishWidget::BackToMenu, 0.8);
}

void UIMLevelFinishWidget::BackToMenu()
{
	GetMyHUD()->MainMenu_Open();
}

bool UIMLevelFinishWidget::CanbeOperating()
{
	return !(bInFadeingIn || bHavPendingNextLevel||bHavPendingBacking);
}
