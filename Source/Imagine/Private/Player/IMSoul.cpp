// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IMSoul.h"
#include"Player/IMCharacter.h"
#include"Player/IMPlayerController.h"
#include"Player/RecordNReplayManager.h"
#include"Components/SoulRNRComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Kismet/GameplayStatics.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"PaperFlipbookComponent.h"
#include"Debug/MyDebug.h"
AIMSoul::AIMSoul(const FObjectInitializer& ObjInit)
{
	RecordNReplayComponent = CreateDefaultSubobject<USoulRNRComponent>("SoulRNR");
}
void AIMSoul::BeginPlay()
{
	Super::BeginPlay();
	ActionBuffer = ActionBufferCache = 0;
	After_bWantsToSoulBack = 0;
}
void AIMSoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float VX = Execute_GetRealVelocity(this).X;
	if (bIsFacingRight && VX < 0) {
		bIsFacingRight = false;
		GetSprite()->SetRelativeScale3D(FVector(-1,1,1));
	}
	else if (!bIsFacingRight && VX > 0) {
		bIsFacingRight = true;
		GetSprite()->SetRelativeScale3D(FVector(1, 1, 1));
	}
	//replaying time has its only actionhandle.
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	if (ERNRState::STATE_Replaying != IMPC->GetRNRState()) {
		ActionBufferCache = ActionBuffer;
		StartAction();
	}
}

void AIMSoul::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AIMSoul::Move);
		EIC->BindAction(IA_Back, ETriggerEvent::Triggered, this, &AIMSoul::SoulBack);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AIMSoul::Jump);
		EIC->BindAction(IA_Swap, ETriggerEvent::Triggered, this, &AIMSoul::SoulSwap);
	}
}
void AIMSoul::SetBody(AIMCharacter* TheBody)
{
	Body = TheBody;
}
void AIMSoul::Move(const FInputActionValue& value)
{
	float Direction = value.Get<float>();
	AddMovementInput(FVector(1, 0, 0), Direction);
}
void AIMSoul::SoulBack()
{
	After_bWantsToSoulBack = true;
}
void AIMSoul::SoulSwap()
{
	ActionBuffer |= ACTION_SWAP;
}
void AIMSoul::StartAction()
{
	if (ActionBuffer & ACTION_SWAP) {
		ActionSwap();
	}
	ActionBuffer = 0;
}
void AIMSoul::ActionSwap()
{
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	if (ERNRState::STATE_Replaying == IMPC->GetRNRState()) {	
		Body->SetActorTransform(GetActorTransform());
		auto BodyCMC = Body->GetCharacterMovement();
		BodyCMC->Velocity = Execute_GetRealVelocity(this);
		BodyCMC->SetMovementMode(Execute_IsRealFalling(this) ? EMovementMode::MOVE_Falling : EMovementMode::MOVE_Walking);
		IMPC->SetRNRState(ERNRState::STATE_None);
		Destroy();
	}
	else {
		SoulBack();
	}
}
void AIMSoul::SetActionBuffer(uint32 Buffer)
{
	ActionBuffer = Buffer;
}
uint32 AIMSoul::GetActionBufferCache()
{
	return ActionBufferCache;
}
void AIMSoul::After_SoulBack()
{
	if (After_bWantsToSoulBack) {
		After_bWantsToSoulBack = false;
		auto IMPC = Cast<AIMPlayerController>(GetController());
		check(IMPC);
		IMPC->Possess(Body);
		Body->OnSoulBack();
	}
}
FVector AIMSoul::GetRealVelocity_Implementation()
{
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	check(IMPC);
	ERNRState RNRState = IMPC->GetRNRState();
	if (RNRState == ERNRState::STATE_Replaying) {
		return Replaying_Velocity;
	}
	else {
		return GetVelocity();
	}
}
bool AIMSoul::IsRealFalling_Implementation()
{
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	ERNRState RNRState = IMPC->GetRNRState();
	if (RNRState == ERNRState::STATE_Replaying) {
		return Replaying_bIsFalling;
	}
	else {
		auto CMC = GetCharacterMovement();
		check(CMC);
		return CMC->IsFalling();
	}
}
void AIMSoul::PossessedBy(AController* NewController)
{
	//For Update IMC 
	Super::PossessedBy(NewController);
	if (auto PC = Cast<APlayerController>(NewController)) {
		if (auto EISubsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if (IMC_Soul) {
				EISubsys->AddMappingContext(IMC_Soul, 0);
			}
		}
	}
}
void AIMSoul::UnPossessed()
{
	//For Update IMC
	if (auto PC = Cast<APlayerController>(GetController())) {
		if (auto EISubsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if (IMC_Soul) {
				EISubsys->RemoveMappingContext(IMC_Soul);
			}
		}
	}
	Super::UnPossessed();
}