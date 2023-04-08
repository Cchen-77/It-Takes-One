// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMCatchableItem.h"
#include "IMKeyLock.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API AIMKeyLock : public AIMCatchableItem
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Key)
	uint8 KeyID;
};
