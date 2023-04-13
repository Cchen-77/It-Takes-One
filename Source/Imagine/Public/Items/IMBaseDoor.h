// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Items/ImBaseItem.h"
#include "IMBaseDoor.generated.h"
class UBaseLockComponent;
class UPaperFlipbook;
DECLARE_MULTICAST_DELEGATE(OnComponentsSaveStateSignature);
DECLARE_MULTICAST_DELEGATE(OnComponentsPrepStateSignature);
UCLASS()
class IMAGINE_API AIMBaseDoor : public AIMBaseItem
{
	GENERATED_BODY()
	
public:
	AIMBaseDoor();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
protected:
	bool bIsOpen;
	bool Saved_bIsOpen;
	void PlayerEnter();
public:
	void UpdateOpeningState(bool IsOpen);
	uint8 GetDoorID();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Door)
	uint8 DoorID = 0;
protected:
	OnComponentsSaveStateSignature OnComponentsSaveState;
	OnComponentsPrepStateSignature OnComponentsPrepState;
public:
	virtual void SaveRNRItemState() override;
	virtual void PrepRNRItemState() override;
	void RegisterLockComponent(UBaseLockComponent* LockComponent);
protected:
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* FB_DoorOpening;
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* FB_DoorClosing;
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* FB_DoorEntering;
};
