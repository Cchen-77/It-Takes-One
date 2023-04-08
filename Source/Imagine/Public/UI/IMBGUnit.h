// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMBGUnit.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UIMBGUnit : public UUserWidget
{
	GENERATED_BODY()
public:
	void Fadein();
	void Fadeout();
protected:
	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* FadeinAnim;
	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* FadeoutAnim;
};
