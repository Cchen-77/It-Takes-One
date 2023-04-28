// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"UI/IMBaseWidget.h"
#include "IMMainMenuWidget.generated.h"

/**
 * 
 */
class AIMBaseHUD;
UCLASS()
class IMAGINE_API UIMMainMenuWidget : public UIMBaseWidget
{
	GENERATED_BODY()

public:
	UIMMainMenuWidget(const FObjectInitializer& ObjInit);
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
protected:
	UPROPERTY(Transient,meta = (BindWidgetAnim))
		UWidgetAnimation* StartBlink;
};
