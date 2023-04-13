// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItem.h"
#include "IMWallController.generated.h"

/**
 * 
 */
class UPaperFlipbook;
UCLASS()
class IMAGINE_API AIMWallController : public AIMBaseItem
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
protected:
	virtual void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallController)
		int WallControllerID;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* FB_ControllerSt1;
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* FB_ControllerSt2;
	bool IsInSt1 = true;
};
