// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include"Player/IMSoulRecord.h"
#include"InputActionValue.h"
#include"Player/CharacterInfoInterface.h"
#include "IMSoul.generated.h"

/**
 * 
 */
class AIMCharacter;
class UInputAction;
class UInputMappingContext;
class USoulRNRComponent;
class AIMCatchableItem;
class USceneComponent;
UENUM(BlueprintType)
enum EAction {
	ACTION_NONE = 0 UMETA(Hidden),
	ACTION_SWAP = 0x1,
	ACTION_THROW = 0x2
};
UCLASS()
class IMAGINE_API AIMSoul : public APaperZDCharacter, public ICharacterInfoInterface
{
	GENERATED_BODY()
public:
	AIMSoul(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadOnly)
		FVector Replaying_Velocity;
	UPROPERTY(BlueprintReadOnly)
		bool Replaying_bIsFalling;
public:
	void SetBody(AIMCharacter* TheBody);
protected:
	AIMCharacter* Body;
	UPROPERTY(VisibleAnywhere, Category = RecordNReplay)
		USoulRNRComponent* RecordNReplayComponent;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Back;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Swap;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Throw;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_Soul;
	
protected:
	void Move(const FInputActionValue& value);
	void SoulBack();
	void SoulSwap();
	//Actions that need to replaying.
	uint32 ActionBuffer;
	//For Buffer Recording!
	uint32 ActionBufferCache;
public:
	void StartAction();
	void ActionSwap();
	void ActionThrow();
	void SetActionBuffer(uint32 Buffer);
	uint32 GetActionBufferCache();
public:
	//Actions for after record
	void After_SoulBack();
protected:
	bool After_bWantsToSoulBack;
public:
	virtual FVector GetRealVelocity_Implementation();
	virtual bool IsRealFalling_Implementation();
protected:
	bool bIsFacingRight = true;
public:
	//Soul in Replaying incounter another recording start.is no need to Save state since it's state triggered.
	AIMCatchableItem* Pausing_CatchedItem;
	void Pause();
	void UnPause();
public:
	AIMCatchableItem* GetCatchedItem();
	bool GetItem(AIMCatchableItem* Key);
	void LoseCatchedItem();
	FVector GetCatchedItemSocketLocation();
	void ThrowItem();
	void DropItem();
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		USceneComponent* ItemSocket;
	UPROPERTY()
		AIMCatchableItem* CatchedItem = nullptr;

};
