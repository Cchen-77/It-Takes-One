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
class AIMSoul;
class UInputMappingContext;
class UInputAction;
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
	void OnSoulBack();
protected:
	UPROPERTY(EditDefaultsOnly, Category = Soul)
		TSubclassOf<AIMSoul> SoulClass;
	void SendSoul();
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
protected:
	bool bFacingRight = true;
	FVector Saved_Velocity;
	bool Saved_bIsFalling;
public:
	void SetSavedState(const FVector& Velocity, bool IsFalling);
	void PrepSavedState();
public:
	virtual FVector GetRealVelocity_Implementation();
	virtual bool IsRealFalling_Implementation();
};
