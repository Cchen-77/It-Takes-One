// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMBaseDoor.h"
#include"Components/BoxComponent.h"
#include"PaperFlipbookComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Player/IMCharacter.h"
#include"Debug/MyDebug.h"
AIMBaseDoor::AIMBaseDoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIMBaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
}
void AIMBaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsOpen) {
		TArray<AActor*> OverlappingActors;
		Collision->GetOverlappingActors(OverlappingActors, AIMCharacter::StaticClass());
		if (!OverlappingActors.IsEmpty()) {
			PlayerEnter();
		}
	}
	bIsOpen = true;
}
void AIMBaseDoor::PlayerEnter()
{
	UMyDebug::Message("Enter!");
}

uint8 AIMBaseDoor::GetDoorID()
{
	return DoorID;
}

void AIMBaseDoor::UpdateOpeningState(bool IsOpen)
{
	bIsOpen &= IsOpen;
}
