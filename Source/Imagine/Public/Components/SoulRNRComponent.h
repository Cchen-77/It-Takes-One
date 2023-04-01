// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RecordNReplayComponent.h"
#include"Player/IMSoulRecord.h"
#include "SoulRNRComponent.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API USoulRNRComponent : public URecordNReplayComponent
{
	GENERATED_BODY()
protected:
	float NowDeltaTime = 0;
	virtual void DoReplaying(float DeltaTime) override;
	virtual void DoRecording(float DeltaTime) override;
	TQueue<FIMSoulRecord> Records;
	void PrepRecord(FIMSoulRecord Record, float alpha);
	void AddRecord(float DeltaTime);
	void ReplayingFinish();
	void AfterRecord();
};
