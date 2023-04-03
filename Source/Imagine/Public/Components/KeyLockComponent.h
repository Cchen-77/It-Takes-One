// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseLockComponent.h"
#include "KeyLockComponent.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UKeyLockComponent : public UBaseLockComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
