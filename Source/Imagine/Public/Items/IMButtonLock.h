// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItem.h"
#include "IMButtonLock.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API AIMButtonLock : public AIMBaseItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
protected:
	UPROPERTY(EditDefaultsOnly,Category = Lock)
	uint32 LockID = 0;
	UPROPERTY(EditDefaultsOnly, Category = Lock)
		float OpenTime = 3;

};
