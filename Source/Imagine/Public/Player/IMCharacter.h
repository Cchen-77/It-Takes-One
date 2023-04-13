// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include"Player/IMSoulRecord.h"
#include"InputActionValue.h"
#include"CharacterInfoInterface.h"
#include "IMCharacter.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPauseSignature);
DECLARE_MULTICAST_DELEGATE(FOnUnPauseSignature);
class AIMSoul;
class UInputMappingContext;
class UInputAction;
class AIMCatchableItem;
class USceneComponent;
UCLASS()
class IMAGINE_API AIMCharacter : public APaperZDCharacter,public ICharacterInfoInterface
{
	GENERATED_BODY()
public:
	AIMCharacter(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void Restart() override;
protected:
	virtual void BeginPlay() override;
public:
	void OnSoulBack(AIMSoul* Soul);
protected:
	UPROPERTY(EditDefaultsOnly, Category = Soul)
		TSubclassOf<AIMSoul> SoulClass;
	void SendSoul();
	bool bFacingRight = true;
	void Move(const FInputActionValue& value);
	bool bCanSendSoul = true;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_Body;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_SendSoul;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Throw;
protected:
	FVector Pausing_Velocity;
	bool Pausing_bIsFalling;
	AIMCatchableItem* Pausing_CatchedItem;
	void Pause();
	void UnPause();
public:
	void SetPausingState(const FVector& Velocity, bool IsFalling, AIMCatchableItem* Item);
	void PrepPausingState();
public:
	virtual FVector GetRealVelocity_Implementation();
	virtual bool IsRealFalling_Implementation();
protected:
	FOnPauseSignature OnPause;
	FOnUnPauseSignature OnUnPause;

public:
	AIMCatchableItem* GetCatchedItem();
	bool GetItem(AIMCatchableItem* Key);
	void LoseCatchedItem();
	FVector GetCatchedItemSocketLocation();
	void ThrowItem();
	void DropItem();
protected:
	UPROPERTY(VisibleAnywhere,Category = Components)
		USceneComponent* ItemSocket;
	UPROPERTY()
		AIMCatchableItem* CatchedItem = nullptr;
public:
	float WorldTime = 0;
};
