// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItem.h"
#include "IMKeyLock.generated.h"

/**
 * 
 */
class UProjectileMovementComponent;
UCLASS()
class IMAGINE_API AIMKeyLock : public AIMBaseItem
{
	GENERATED_BODY()
public:
	AIMKeyLock();
	virtual void Tick(float DeltaTime) override;
	virtual void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SaveRNRItemState();
	virtual void PrepRNRItemState();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lock)
		uint8 KeyID;
	void OnKeyDrop(FVector Direction);
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UProjectileMovementComponent* ProjectileMovement;
	AActor* Holder = nullptr;
	AActor* Saved_Holder = nullptr;
	float RemainingTime = -1;
	float Saved_RemainingTime = -1;
	FVector Saved_Velocity; 
};
