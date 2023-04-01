// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RecordNReplayManager.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERNRState :uint8{
	STATE_None,
	STATE_Replaying,
	STATE_Recording
};
UCLASS()
class IMAGINE_API URecordNReplayManager : public UObject
{
	GENERATED_BODY()
public:
	void SetRNRState(ERNRState State);
	ERNRState GetRNRState() const;
protected:
	ERNRState RNRState = ERNRState::STATE_None;
};
