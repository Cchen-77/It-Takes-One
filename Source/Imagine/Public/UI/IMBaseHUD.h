// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IMBaseHUD.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EHUDMode :uint8{
	MODE_MAINMENU UMETA(Displayname = MainMenu),
	MODE_GAMEPLAY UMETA(Displayname = Gameplay)
};
class UIMTransitionWidget;
class UIMMainMenuWidget;
class UIMLevelSelectingWidget;
class UIMESCMenuWidget;
class UIMLevelFinishWidget;
UCLASS()
class IMAGINE_API AIMBaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void Transition_Fadein();
	UFUNCTION(BlueprintCallable)
		void Transition_Fadeout();
	UFUNCTION(BlueprintCallable)
		void MainMenu_Open();
	UFUNCTION(BlueprintCallable)
		void LevelSelecting_Open();
	UFUNCTION(BlueprintCallable)
		void LevelSelecting_Close();
	UFUNCTION(BlueprintCallable)
		void ESCMenu_Open();
	UFUNCTION(BlueprintCallable)
		void ESCMenu_Close();
	UFUNCTION(BlueprintCallable)
		void LevelFinish_Open();
protected:
	UPROPERTY(EditDefaultsOnly, Category = Setting)
		EHUDMode HUDMode;
 	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMTransitionWidget> TransitionWidgetClass;
	UPROPERTY()
		UIMTransitionWidget* TransitionWidget;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
		UIMMainMenuWidget* MainMenuWidget;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMLevelSelectingWidget> LevelSelectingWidgetClass;
	UPROPERTY()
		UIMLevelSelectingWidget* LevelSelectingWidget;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMESCMenuWidget> ESCMenuWidgetClass;
	UPROPERTY()
		UIMESCMenuWidget* ESCMenuWidget;
	UPROPERTY(EditDefaultsOnly, Category = UMG)
		TSubclassOf<UIMLevelFinishWidget> LevelFinishWidgetClass;
	UPROPERTY()
		UIMLevelFinishWidget* LevelFinishWidget;
private:
	void SetInputModeUIOnly(UUserWidget* FocusWidget);
	void SetInputModeGameplayOnly();
};
