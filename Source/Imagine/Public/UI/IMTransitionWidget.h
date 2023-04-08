// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMTransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UIMTransitionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized();
	void Fadein();
	void FadeOut();

};
