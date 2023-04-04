// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItem.h"
#include "IMCatchableItem.generated.h"

/**
 * 
 */
class UProjectileMovementComponent;
UCLASS()
class IMAGINE_API AIMCatchableItem : public AIMBaseItem
{
	GENERATED_BODY()
public:
	AIMCatchableItem();
	virtual void Tick(float DeltaTime) override;
	virtual void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SaveRNRItemState();
	virtual void PrepRNRItemState();
	void OnBeingThrow(FVector Direction);
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, Category = Dropping)
		float ThrowingSpeed = 300;

	AActor* Holder = nullptr;
	AActor* Saved_Holder = nullptr;

	FVector Saved_Velocity; 

	FVector Saved_Location;

	bool Saved_bProjectileMoving;
};
