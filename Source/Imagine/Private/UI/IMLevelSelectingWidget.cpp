// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMLevelSelectingWidget.h"
#include"UI/IMBaseHUD.h"
#include"Kismet/GameplayStatics.h"
#include"IMBaseGameInstance.h"
UIMLevelSelectingWidget::UIMLevelSelectingWidget(const FObjectInitializer& Objinit) :Super(Objinit)
{
	bIsFocusable = true;
}
void UIMLevelSelectingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bHavPendingOpening = false;
	CurrentLevelIndex = 0;
	MyGI = nullptr;
	MyHUD = nullptr;
	LevelNums = GetMyGI()->GetLevelNums();
	check(GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache));
	RefreshWidget();
}
FReply UIMLevelSelectingWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	FKey TheKey = InKeyEvent.GetKey();
	if (bHavPendingOpening) return FReply::Handled();
	if (TheKey == EKeys::D || TheKey == EKeys::Right) {
		R_ChangeLevel();
	}
	if (TheKey == EKeys::A || TheKey == EKeys::Left) {
		L_ChangeLevel();
	}
	if (TheKey == EKeys::SpaceBar) {
		OpenLevel_Pre();
	}
	return FReply::Handled();
}

void UIMLevelSelectingWidget::RefreshWidget()
{

}

void UIMLevelSelectingWidget::L_ChangeLevel()
{
	if (bHavPendingOpening) return;
	if (CurrentLevelIndex == 0) return;
	--CurrentLevelIndex;
	GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache);
	RefreshWidget();

}

void UIMLevelSelectingWidget::R_ChangeLevel()
{
	if (bHavPendingOpening) return;
	if (CurrentLevelIndex == LevelNums - 1) return;
	++CurrentLevelIndex;
	GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache);
	RefreshWidget();
}

void UIMLevelSelectingWidget::OpenLevel_Pre()
{
	if (bHavPendingOpening) return;
	bHavPendingOpening = true;
	GetMyHUD()->Transition_Fadein();
	GetWorld()->GetTimerManager().SetTimer(Transition_Timer, this, &UIMLevelSelectingWidget::OpenLevel, 0.8);
}
void UIMLevelSelectingWidget::OpenLevel() {
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelInfoCache.LevelName);
}
AIMBaseHUD* UIMLevelSelectingWidget::GetMyHUD()
{
	if (!MyHUD) {
		check(GetOwningPlayer());
		MyHUD = Cast<AIMBaseHUD>(GetOwningPlayer()->GetHUD());
		check(MyHUD);
	}
	return MyHUD;
}

UIMBaseGameInstance* UIMLevelSelectingWidget::GetMyGI()
{
	if (!MyGI) {
		MyGI = Cast<UIMBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		check(MyGI);
	}
	return MyGI;
}
