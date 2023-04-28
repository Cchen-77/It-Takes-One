// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"UI/IMBaseWidget.h"
#include "IMBGUnit.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UIMBGUnit : public UIMBaseWidget
{
	GENERATED_BODY()
public:
	void Fadein();
	void Fadeout();
protected:
	UPROPERTY(Transient,meta = (BindWidgetAnim))
		UWidgetAnimation* FadeinAnim;
	UPROPERTY(Transient,meta = (BindWidgetAnim))
		UWidgetAnimation* FadeoutAnim;
};
