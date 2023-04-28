// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"UI/IMBaseWidget.h"
#include "IMLevelFinishWidget.generated.h"

/**
 * 
 */
class UButton;
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMLevelFinishWidget : public UIMBaseWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
protected:
	FTimerHandle Transition_Timer;
	UFUNCTION()
		void NextLevel_Pre();
	bool bHavPendingNextLevel = false;
	FName NextLevelNameCache;
	void NextLevel();
protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeinAnim;
	bool bInFadeingIn;
	UFUNCTION()
		void OnFadinginFinish();
	FTimerHandle Fadingin_Timer;
	UPROPERTY(meta = (BindWidget))
	UButton* Next;
	UPROPERTY(meta = (BindWidget))
		UButton* MainMenu;
	UFUNCTION()
		void BackToMenu_Pre();
	bool bHavPendingBacking;
	void BackToMenu();
	

protected:
	bool CanbeOperating();
};
