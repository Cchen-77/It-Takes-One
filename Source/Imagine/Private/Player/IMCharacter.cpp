// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Player/IMPlayerController.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"Kismet/KismetMathLibrary.h"
#include"PaperFlipbookComponent.h"
#include"Components/SceneComponent.h"
#include"Items/IMKeyLock.h"
#include"Debug/DebugCMC.h"
#include"Debug/MyDebug.h"
AIMCharacter::AIMCharacter(const FObjectInitializer& ObjInit)
{
	KeySocket = CreateDefaultSubobject<USceneComponent>("KeySocket");
	KeySocket->SetupAttachment(GetSprite());
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
		EIC->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &AIMCharacter::ThrowKey);
	}
}
void AIMCharacter::PossessedBy(AController* NewController)
{
	auto CMC = GetCharacterMovement();
	Super::PossessedBy(NewController);
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
		//bCanSendSoul = false;
		Pause();
		auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		check(IMPC);
		IMPC->SaveRNRItemsState();
		AIMSoul* MySoul = GetWorld()->SpawnActorDeferred<AIMSoul>(SoulClass, GetActorTransform());
		MySoul->SetBody(this);
		MySoul->FinishSpawning(GetActorTransform());
		IMPC->Possess(MySoul);
	}	
}
void AIMCharacter::Move(const FInputActionValue& value)
{
	float Direction = value.Get<float>();
	AddMovementInput(FVector(1, 0, 0), Direction);
}
void AIMCharacter::Pause()
{
	CustomTimeDilation = 0;
	auto CMC = GetCharacterMovement();
	check(CMC);
	SetPausingState(GetVelocity(), CMC->IsFalling(),HoldingKey);
	OnPause.Broadcast();
}
void AIMCharacter::UnPause()
{
	PrepPausingState();
	CustomTimeDilation = 1;
	OnUnPause.Broadcast();
}
void AIMCharacter::SetPausingState(const FVector& Velocity, bool IsFalling,AIMKeyLock* Key)
{
	Pausing_Velocity = Velocity;
	Pausing_bIsFalling = IsFalling;
	Pausing_HoldingKey = HoldingKey;

}
void AIMCharacter::PrepPausingState()
{
	auto CMC = GetCharacterMovement();
	check(CMC);
	CMC->Velocity = Pausing_Velocity;
	if (Pausing_bIsFalling) {
		CMC->SetMovementMode(EMovementMode::MOVE_Falling);
	}
	HoldingKey = Pausing_HoldingKey;
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
void AIMCharacter::OnSoulBack(AIMSoul* Soul)
{
	UnPause();
	OnPause.AddUObject(Soul, &AIMSoul::Pause);
	OnUnPause.AddUObject(Soul, &AIMSoul::UnPause);
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	IMPC->PrepRNRItemsState();
}

AIMKeyLock* AIMCharacter::GetHoldingKey()
{
	return HoldingKey;
}
bool AIMCharacter::GetKey(AIMKeyLock* Key)
{
	if (!HoldingKey) {
		HoldingKey = Key;
		return true;
	}
	else {
		return false;
	}
}

void AIMCharacter::LoseKey()
{
	HoldingKey = nullptr;
}

FVector AIMCharacter::GetKeySocketLocation()
{
	return KeySocket->GetComponentLocation();
}

void AIMCharacter::ThrowKey()
{
	if (HoldingKey) {
		if (bFacingRight){
			HoldingKey->OnBeingThrow(FVector(1, 0, 1));
		}
		else {
			HoldingKey->OnBeingThrow(FVector(-1, 0, 1));
		}
		HoldingKey = nullptr;
	}
}
