// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecordNReplayComponent.generated.h"
UENUM(BlueprintType)
enum class ERNRState :uint8 {
	STATE_None,
	STATE_Replaying,
	STATE_Recording
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMAGINE_API URecordNReplayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URecordNReplayComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	ERNRState GetRNRState() const;
	void SetRNRState(ERNRState State);
protected:
	float NowDeltaTime = 0;
	virtual void DoRecording(float DeltaTime);
	virtual void DoReplaying(float DeltaTime);
	ERNRState RNRState = ERNRState::STATE_None;
	
};