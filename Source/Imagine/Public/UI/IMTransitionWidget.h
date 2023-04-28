// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"UI/IMBaseWidget.h"
#include "IMTransitionWidget.generated.h"

/**
 * 
 */
class UUniformGridPanel;
class UIMBGUnit;
UCLASS()
class IMAGINE_API UIMTransitionWidget : public UIMBaseWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	UFUNCTION(BlueprintCallable)
	void Fadein();
	UFUNCTION(BlueprintCallable)
	void FadeOut();
protected:
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* Grid;
	UPROPERTY()
		TArray<UIMBGUnit*> BGUnits;
	UPROPERTY(EditDefaultsOnly, Category = BG)
		TSubclassOf<UIMBGUnit> BGUnitClass;
	UPROPERTY(EditDefaultsOnly, Category = BG)
		uint32 GridRows;
	UPROPERTY(EditDefaultsOnly, Category = BG)
		uint32 GridCollums;
	
protected:
	float NowTime = 0;
	UPROPERTY(EditDefaultsOnly,Category = Transition)
	float BlendingTime = 0;
	bool bFadeout = true;
	uint32 OldDis = 0;
};
