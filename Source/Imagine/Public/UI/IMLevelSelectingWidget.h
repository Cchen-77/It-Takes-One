// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"IMInfoTypes.h"
#include "IMLevelSelectingWidget.generated.h"

/**
 * 
 */
class UIMBaseGameInstance;
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMLevelSelectingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UIMLevelSelectingWidget(const FObjectInitializer& Objinit);
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
protected:
	FLevelInfo CurrentLevelInfoCache;
	uint32 CurrentLevelIndex = 0;
	uint32 LevelNums;
protected:
	void L_ChangeLevel();
	void R_ChangeLevel();
	
	bool bHavPendingOpening = false;
	void OpenLevel_Pre();
	void OpenLevel();
	FTimerHandle Transition_Timer;
	void RefreshWidget();

	
protected:
	UIMBaseGameInstance* GetMyGI();
	AIMBaseHUD* GetMyHUD();
private:
	UIMBaseGameInstance* MyGI = nullptr;
	AIMBaseHUD* MyHUD = nullptr;
};
