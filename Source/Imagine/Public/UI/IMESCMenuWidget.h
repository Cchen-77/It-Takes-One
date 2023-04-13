// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMESCMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMESCMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UIMESCMenuWidget(const FObjectInitializer& ObjInit);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	AIMBaseHUD* GetMyHUD();
protected:
	UFUNCTION()
	void BackToMainMenu_Pre();
	bool bHavPendingBacking;
	FTimerHandle Transition_Timer;
	void BackToMainMenu();
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenu;
private:
	AIMBaseHUD* MyHUD;
};
