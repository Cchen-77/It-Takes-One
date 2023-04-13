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
class AIMBaseItem;
class UInputMappingContext;
class UInputAction;
class UIMFXSpawner;
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
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		TSubclassOf<ACameraActor> IMCameraClass;
	UPROPERTY()
		ACameraActor* IMCamera;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		FVector CameraStartLocation;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		bool bIsCameraBlending;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		bool bIsCameraLocked;
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
protected:
	virtual void SetupInputComponent() override;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_Base;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Esc;
	void OnEsc();
protected:
	UFUNCTION(BlueprintCallable)
		float GetWorldTime();
public:
	void SpawnFX();
protected:
	UPROPERTY(EditDefaultsOnly, Category = FX)
		TSubclassOf<UIMFXSpawner> FXSpawnerClass;
	UIMFXSpawner* FXSpawner;
};
