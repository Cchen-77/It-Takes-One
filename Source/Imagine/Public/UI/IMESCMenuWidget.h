// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"UI/IMBaseWidget.h"
#include "IMESCMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMESCMenuWidget : public UIMBaseWidget
{
	GENERATED_BODY()

public:
	UIMESCMenuWidget(const FObjectInitializer& ObjInit);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
protected:
	FTimerHandle Transition_Timer;
	UFUNCTION()
	void BackToMainMenu_Pre();
	bool bHavPendingBacking;
	void BackToMainMenu();
	UFUNCTION()
	void Restart_Pre();
	bool bHavPendingRestarting;
	void Restart();
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* Resume;
	UPROPERTY(meta = (BindWidget))
		UButton* Control;

	UPROPERTY(meta = (BindWidget))
		UButton* RestartCurrent;	

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenu;
	bool CanbeOperating() const;
};
