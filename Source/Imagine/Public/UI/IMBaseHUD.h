// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IMBaseHUD.generated.h"

/**
 * 
 */
class UIMTransitionWidget;
class UIMMainMenuWidget;
UCLASS()
class IMAGINE_API AIMBaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void Transition_Fadein();
	UFUNCTION(BluepritnCallable)
		void Transition_Fadeout();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMTransitionWidget> TransitionWidgetClass;
	UPROPERTY()
		UIMTransitionWidget* TransitionWidget;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
		UIMMainMenuWidget* MainMenuWidget;
};
