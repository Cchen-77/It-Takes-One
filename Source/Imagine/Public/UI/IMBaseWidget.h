// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMBaseWidget.generated.h"

/**
 * 
 */
class UIMBaseGameInstance;
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMBaseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UIMBaseGameInstance* GetMyGI();
	AIMBaseHUD* GetMyHUD();
private:
	UIMBaseGameInstance* MyGI = nullptr;
	AIMBaseHUD* MyHUD = nullptr;
};
