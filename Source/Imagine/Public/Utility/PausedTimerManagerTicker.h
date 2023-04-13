// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PausedTimerManagerTicker.generated.h"

UCLASS()
class IMAGINE_API APausedTimerManagerTicker : public AActor
{
	GENERATED_BODY()
	
public:	
	APausedTimerManagerTicker();
	virtual void Tick(float DeltaTime) override;
};
