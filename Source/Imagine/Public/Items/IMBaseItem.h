// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMBaseItem.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;
class UPaperZDAnimationComponent;
class UPaperFlipbook;
UCLASS()
class IMAGINE_API AIMBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AIMBaseItem();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPaperFlipbookComponent* Sprite;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPaperZDAnimationComponent* PaperZDAnimation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void Trigger(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void TriggerFinish(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void SaveRNRItemState();
	virtual void PrepRNRItemState();
protected:
	UPROPERTY(EditDefaultsOnly,Category = Sprite)
	UPaperFlipbook* FB_Triggered;
	UPROPERTY(EditDefaultsOnly,Category = Sprite)
	UPaperFlipbook* FB_TriggerFinish;
};
