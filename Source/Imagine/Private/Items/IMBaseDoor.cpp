// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMBaseDoor.h"
#include"Components/BoxComponent.h"
#include"Components/BaseLockComponent.h"
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
	Sprite->SetLooping(false);
}
void AIMBaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsOpen) {
		if (FB_DoorOpening) {
			Sprite->SetFlipbook(FB_DoorOpening);
			Sprite->Play();
		
		}
		TArray<AActor*> OverlappingActors;
		Collision->GetOverlappingActors(OverlappingActors, AIMCharacter::StaticClass());
		if (!OverlappingActors.IsEmpty()) {
			if (FB_DoorEntering) {
				Sprite->SetFlipbook(FB_DoorEntering);
			}
			PlayerEnter();
		}
	}
	else {
		if (FB_DoorClosing) {
			Sprite->SetFlipbook(FB_DoorClosing);
			Sprite->Play();
		}
	}
	bIsOpen = true;
}
void AIMBaseDoor::PlayerEnter()
{
	if (FB_DoorEntering) {
		Sprite->SetFlipbook(FB_DoorEntering);
		Sprite->Play();
	}
	UMyDebug::Message("Enter!");
}

uint8 AIMBaseDoor::GetDoorID()
{
	return DoorID;
}
void AIMBaseDoor::SaveRNRItemState()
{
	Saved_bIsOpen = bIsOpen;
	OnComponentsSaveState.Broadcast();
}

void AIMBaseDoor::PrepRNRItemState()
{
	bIsOpen = Saved_bIsOpen;
	OnComponentsPrepState.Broadcast();
}

void AIMBaseDoor::RegisterLockComponent(UBaseLockComponent* LockComponent)
{
	OnComponentsSaveState.AddUObject(LockComponent, &UBaseLockComponent::SaveState);
	OnComponentsPrepState.AddUObject(LockComponent, &UBaseLockComponent::PrepState);
}

void AIMBaseDoor::UpdateOpeningState(bool IsOpen)
{
	bIsOpen &= IsOpen;
}

