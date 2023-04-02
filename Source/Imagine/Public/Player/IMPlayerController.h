// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IMPlayerController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FSaveRNRItemsStateSignature);
DECLARE_MULTICAST_DELEGATE(FPrepRNRItemsStateSignature);
class ACameraActor;
class AIMBaseItem;
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
	void SaveRNRItemsState();
	void PrepRNRItemsState();
	void RNRItemRegister(AIMBaseItem* Item);
protected:
	FSaveRNRItemsStateSignature OnSaveRNRItemsState;
	FPrepRNRItemsStateSignature OnPrepRNRItemsState;
};
