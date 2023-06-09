// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IMPlayerController.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Items/IMBaseItem.h"
#include"Camera/CameraActor.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"UI/IMBaseHUD.h"
#include"FX/IMFXSpawner.h"
#include"Debug/MyDebug.h"
AIMPlayerController::AIMPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AIMPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsCameraLocked) {
		FVector ActorLocation = GetPawn()->GetActorLocation();
		if (bIsCameraBlending) {
			CameraBlendTo(ActorLocation, DeltaTime);
		}
		else {
			CameraMoveto(ActorLocation);
		}
	}
}

void AIMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	IMCamera = GetWorld()->SpawnActor<ACameraActor>(IMCameraClass, CameraStartLocation, FRotator(0, -90, 0));
	SetViewTarget(IMCamera);
	if (auto EISubsys = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		EISubsys->AddMappingContext(IMC_Base, 1);
	}
	FXSpawner = NewObject<UIMFXSpawner>(this, FXSpawnerClass);
	check(FXSpawner);
}

void AIMPlayerController::CameraMoveto(FVector Location)
{
	Location.Y = CameraStartLocation.Y;
	IMCamera->SetActorLocation(Location);
}

void AIMPlayerController::CameraBlendTo(FVector Location, float DeltaTime)
{
	Location.Y = CameraStartLocation.Y;
	FVector OldLocation = IMCamera->GetActorLocation();
	if ((Location - OldLocation).IsNearlyZero(0.01)) {
		CameraMoveto(Location);
		return;
	}
	FVector DstLocation = FMath::VInterpTo(OldLocation, Location, DeltaTime, BlendingSpeed);
	IMCamera->SetActorLocation(DstLocation);
}

void AIMPlayerController::SaveRNRItemsState()
{
	OnSaveRNRItemsState.Broadcast();
}
void AIMPlayerController::PrepRNRItemsState()
{
	OnPrepRNRItemsState.Broadcast();
}

void AIMPlayerController::RNRItemRegister(AIMBaseItem* Item)
{
	OnSaveRNRItemsState.AddUObject(Item, &AIMBaseItem::SaveRNRItemState);
	OnPrepRNRItemsState.AddUObject(Item, &AIMBaseItem::PrepRNRItemState);
}

void AIMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (auto EIC = Cast<UEnhancedInputComponent>(InputComponent)) {
		EIC->BindAction(IA_Esc, ETriggerEvent::Triggered, this, &AIMPlayerController::OnEsc);
	}
}

void AIMPlayerController::OnEsc()
{
	auto IMHUD = Cast<AIMBaseHUD>(GetHUD());
	check(IMHUD);
	IMHUD->ESCMenu_Open();
}

float AIMPlayerController::GetWorldTime()
{
	if (auto IMCharacter = Cast<AIMCharacter>(GetPawn())) {
		return IMCharacter->WorldTime;
	}
	if (auto IMSoul = Cast<AIMSoul>(GetPawn()) ){
		return IMSoul->WorldTime;
	}
	return 0.0f;
}

void AIMPlayerController::SpawnFX(FName FXName, FVector Location)
{
	check(FXSpawner);
	bool success = FXSpawner->SpawnFX(FXName, Location);
	if (success) {

	}
	else {
		UMyDebug::Message("SpawnFail!");
	}
}



