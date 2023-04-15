// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMLevelSelectingWidget.h"
#include"UI/IMBaseHUD.h"
#include"Kismet/GameplayStatics.h"
#include"IMBaseGameInstance.h"
#include"Components/TextBlock.h"
#include"Components/Button.h"
UIMLevelSelectingWidget::UIMLevelSelectingWidget(const FObjectInitializer& Objinit) :Super(Objinit)
{
	bIsFocusable = true;
}
void UIMLevelSelectingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button_Pre->OnClicked.AddDynamic(this, &UIMLevelSelectingWidget::L_ChangeLevel);
	Button_Next->OnClicked.AddDynamic(this, &UIMLevelSelectingWidget::R_ChangeLevel);
	Button_Pre->IsFocusable = false;
	Button_Next->IsFocusable = false;
	Button_Go->OnClicked.AddDynamic(this, &UIMLevelSelectingWidget::OpenLevel_Pre);
	Button_Go->IsFocusable = false;
	Button_Back->OnClicked.AddDynamic(this, &UIMLevelSelectingWidget::CloseSelf_Pre);
	Button_Back->IsFocusable = false;
}
void UIMLevelSelectingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bHavPendingTransition = false;
	bHavPendingClosing = false;
	CurrentLevelIndex = 0;
	MyGI = nullptr;
	MyHUD = nullptr;
	LevelNums = GetMyGI()->GetLevelNums();
	check(GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache));
	RefreshWidget();

	bInFadingIn = true;
	PlayAnimation(BG_Fadein);
	GetWorld()->GetTimerManager().SetTimer(Timer_FadingIn, this, &UIMLevelSelectingWidget::OnFadinginFinish, 0.5);
}
FReply UIMLevelSelectingWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	FKey TheKey = InKeyEvent.GetKey();
	if (!CanbeOperating()) return FReply::Handled();
	if (TheKey == EKeys::D || TheKey == EKeys::Right) {
		R_ChangeLevel();
	}
	if (TheKey == EKeys::A || TheKey == EKeys::Left) {
		L_ChangeLevel();
	}
	if (TheKey == EKeys::SpaceBar) {
		OpenLevel_Pre();
	}
	if (TheKey == EKeys::Escape) {
		CloseSelf_Pre();
	}
	return FReply::Handled();
}

void UIMLevelSelectingWidget::RefreshWidget()
{
	if (LevelNameText) {
		LevelNameText->SetText(FText::FromName(CurrentLevelInfoCache.LevelName));
	}
}
void UIMLevelSelectingWidget::L_ChangeLevel()
{
	if (!CanbeOperating()) return;
	if (CurrentLevelIndex == 0) return;
	--CurrentLevelIndex;
	GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache);
	RefreshWidget();

}

void UIMLevelSelectingWidget::R_ChangeLevel()
{
	if (!CanbeOperating()) return;
	if (CurrentLevelIndex == LevelNums - 1) return;
	++CurrentLevelIndex;
	GetMyGI()->GetLevelInfo(CurrentLevelIndex, CurrentLevelInfoCache);
	RefreshWidget();
}

void UIMLevelSelectingWidget::OpenLevel_Pre()
{
	if (!CanbeOperating()) return;
	bHavPendingTransition = true;
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

void UIMLevelSelectingWidget::OnFadinginFinish()
{
	bInFadingIn = false;
}

void UIMLevelSelectingWidget::CloseSelf_Pre()
{
	if (!CanbeOperating()) return;
	PlayAnimation(BG_Fadeout);
	bHavPendingClosing = true;
	GetWorld()->GetTimerManager().SetTimer(Closing_Timer, this, &UIMLevelSelectingWidget::CloseSelf, 0.5);
}
void UIMLevelSelectingWidget::CloseSelf()
{
	GetMyHUD()->LevelSelecting_Close();
}
bool UIMLevelSelectingWidget::CanbeOperating() const
{
	return !(bHavPendingClosing || bHavPendingTransition||bInFadingIn);
}
UIMBaseGameInstance* UIMLevelSelectingWidget::GetMyGI()
{
	if (!MyGI) {
		MyGI = Cast<UIMBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		check(MyGI);
	}
	return MyGI;
}
