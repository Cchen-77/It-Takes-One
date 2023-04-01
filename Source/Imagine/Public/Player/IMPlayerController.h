// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include"Player/RecordNReplayManager.h"
#include "IMPlayerController.generated.h"

/**
 * 
 */
class ACameraActor;
class URecordNReplayManager;
UCLASS()
class IMAGINE_API AIMPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AIMPlayerController();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY()
		ACameraActor* IMCamera;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float CameraDistance = 200;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		bool bIsCameraBlending;
	void CameraMoveto(FVector Location);
	void CameraBlendTo(FVector Location, float DeltaTime);
	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (EditCondition = "bIsCameraBlending"))
		float BlendingSpeed;

public:
	URecordNReplayManager* GetRecordNReplayManager() const;
	ERNRState GetRNRState() const;
	void SetRNRState(ERNRState State);
protected:
	UPROPERTY()
		URecordNReplayManager* RecordNReplayManager;
	
};
