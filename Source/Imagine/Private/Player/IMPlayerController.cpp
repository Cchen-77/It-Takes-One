// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IMPlayerController.h"
#include"Items/IMBaseItem.h"
#include"Camera/CameraActor.h"
AIMPlayerController::AIMPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AIMPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ActorLocation = GetPawn()->GetActorLocation();
	if (bIsCameraBlending) {
		CameraBlendTo(ActorLocation,DeltaTime);
	}
	else {
		CameraMoveto(ActorLocation);
	}
}

void AIMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	IMCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), FVector(0, CameraDistance, 0), FRotator(0, -90, 0));
	SetViewTarget(IMCamera);
}

void AIMPlayerController::CameraMoveto(FVector Location)
{
	Location.Y = CameraDistance;
	IMCamera->SetActorLocation(Location);
}

void AIMPlayerController::CameraBlendTo(FVector Location, float DeltaTime)
{
	Location.Y = CameraDistance;
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



