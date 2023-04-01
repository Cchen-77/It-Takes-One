// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Items/ImBaseItem.h"
#include "IMBaseDoor.generated.h"

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
	void PlayerEnter();
public:
	void UpdateOpeningState(bool IsOpen);
	uint8 GetDoorID();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Door)
	uint8 DoorID = 0;
};
