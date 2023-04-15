// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"IMInfoTypes.h"
#include"Engine/DataTable.h"
#include "IMLevelSelectingWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLevelDataRow :public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> TumbnailTexture;
};
class UIMBaseGameInstance;
class AIMBaseHUD;
class UTextBlock;
class UButton;
UCLASS()
class IMAGINE_API UIMLevelSelectingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UIMLevelSelectingWidget(const FObjectInitializer& Objinit);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* LevelNameText;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Pre;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Next;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Back;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Go;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* BG_Fadein;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* BG_Fadeout;

protected:
	FLevelInfo CurrentLevelInfoCache;
	uint32 CurrentLevelIndex = 0;
	uint32 LevelNums;
protected:
	UFUNCTION()
	void L_ChangeLevel();
	UFUNCTION()
	void R_ChangeLevel();
	
	bool bInFadingIn = false;
	FTimerHandle Timer_FadingIn;
	void OnFadinginFinish();

	bool bHavPendingTransition = false;
	UFUNCTION()
	void OpenLevel_Pre();
	void OpenLevel();
	FTimerHandle Transition_Timer;
	void RefreshWidget();

	bool bHavPendingClosing = false;
	UFUNCTION()
	void CloseSelf_Pre();
	FTimerHandle Closing_Timer;
	void CloseSelf();
	bool CanbeOperating() const;

protected:
	UIMBaseGameInstance* GetMyGI();
	AIMBaseHUD* GetMyHUD();
private:
	UIMBaseGameInstance* MyGI = nullptr;
	AIMBaseHUD* MyHUD = nullptr;
};
