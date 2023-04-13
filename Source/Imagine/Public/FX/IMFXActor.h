// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMFXActor.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;
UCLASS()
class IMAGINE_API AIMFXActor : public AActor
{
	GENERATED_BODY()
public:	
	AIMFXActor();
protected:
	virtual void BeginPlay() override;
	UPROPERTY()
		UPaperFlipbookComponent* FXSprite;
	UPROPERTY()
		UPaperFlipbook* FXFlipbook;
	UFUNCTION()
		void OnFXFinish();
public:	
	virtual void Tick(float DeltaTime) override;

};
