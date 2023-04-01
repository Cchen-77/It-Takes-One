// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInfoInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCharacterInfoInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IMAGINE_API ICharacterInfoInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	 FVector GetRealVelocity();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool IsRealFalling();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
