// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugCMC.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UDebugCMC : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PhysFalling(float deltaTime, int32 Iterations);
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0);
};
