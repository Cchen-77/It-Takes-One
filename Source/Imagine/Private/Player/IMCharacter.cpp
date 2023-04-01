// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Player/IMPlayerController.h"
#include"Player/RecordNReplayManager.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"Kismet/KismetMathLibrary.h"
#include"PaperFlipbookComponent.h"
#include"Debug/DebugCMC.h"
#include"Debug/MyDebug.h"
AIMCharacter::AIMCharacter(const FObjectInitializer& ObjInit)
{
	
}
void AIMCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto CMC = GetCharacterMovement();
	check(CMC);
	CMC->SetDefaultMovementMode();
	bCanSendSoul = true;	
}
void AIMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float XVelocity = GetVelocity().X;
	if (bFacingRight && XVelocity < 0) {
		bFacingRight = false;
		GetSprite()->SetRelativeScale3D(FVector(-1, 1, 1));
	}
	else if (!bFacingRight && XVelocity>0) {
		bFacingRight = true;
		GetSprite()->SetRelativeScale3D(FVector(1, 1, 1));
	}
	auto CMC = GetCharacterMovement();
}
void AIMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(IA_SendSoul, ETriggerEvent::Triggered, this, &AIMCharacter::SendSoul);
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AIMCharacter::Move);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AIMCharacter::Jump);
	}
}
void AIMCharacter::PossessedBy(AController* NewController)
{
	auto CMC = GetCharacterMovement();
	Super::PossessedBy(NewController);
	CustomTimeDilation = 1;
	if (auto PC = Cast<APlayerController>(NewController)) {
		if (auto EISubsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if (IMC_Body) {
				EISubsys->AddMappingContext(IMC_Body, 0);
			}
		}
	}
}
void AIMCharacter::UnPossessed()
{
	if (auto PC = Cast<APlayerController>(GetController())) {
		if (auto EISubsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if (IMC_Body) {
				EISubsys->RemoveMappingContext(IMC_Body);
			}
		}
	}
	CustomTimeDilation = 0;
	Super::UnPossessed();
}

void AIMCharacter::Restart()
{
	APawn::Restart();
	JumpCurrentCount = 0;
	JumpCurrentCountPreJump = 0;
	bPressedJump = false;
	ResetJumpState();
	UnCrouch(true);
}
void AIMCharacter::SendSoul()
{
	if (!bCanSendSoul) return;
	if (SoulClass) {
		bCanSendSoul = false;
		auto CMC = GetCharacterMovement();
		check(CMC);
		SetSavedState(GetVelocity(), CMC->IsFalling());
		AIMSoul* MySoul = GetWorld()->SpawnActorDeferred<AIMSoul>(SoulClass, GetActorTransform());
		MySoul->SetBody(this);
		auto IMPC = Cast<AIMPlayerController>(GetController());
		check(IMPC);
		MySoul->FinishSpawning(GetActorTransform());
		IMPC->Possess(MySoul);
	}	
}
void AIMCharacter::Move(const FInputActionValue& value)
{
	float Direction = value.Get<float>();
	AddMovementInput(FVector(1, 0, 0), Direction);
}
void AIMCharacter::SetSavedState(const FVector& Velocity, bool IsFalling)
{
	Saved_Velocity = Velocity;
	Saved_bIsFalling = IsFalling;
}
void AIMCharacter::PrepSavedState()
{
	auto CMC = GetCharacterMovement();
	check(CMC);
	CMC->Velocity = Saved_Velocity;
	if (Saved_bIsFalling) {
		CMC->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}
FVector AIMCharacter::GetRealVelocity_Implementation()
{
	return GetVelocity();
}
bool AIMCharacter::IsRealFalling_Implementation()
{
	auto CMC = GetCharacterMovement();
	check(CMC);
	return CMC->IsFalling();
}
void AIMCharacter::OnSoulBack()
{
	PrepSavedState();
}
