// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMKeyLock.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Components/BoxComponent.h"
AIMKeyLock::AIMKeyLock()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovement->SetUpdatedComponent(Collision);
}

void AIMKeyLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Holder) {
		ProjectileMovement->StopMovementImmediately();
		if (auto IMCharacter = Cast<AIMCharacter>(Holder)) {
			SetActorLocation(IMCharacter->GetKeySocketLocation());
		}
		else if (auto IMSoul = Cast<AIMSoul>(Holder)) {
			SetActorLocation(IMCharacter->GetKeySocketLocation());
		}
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else {
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AIMKeyLock::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Trigger(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (auto IMCharacter = Cast<AIMCharacter>(OtherActor)) {
		if (IMCharacter->GetKey(this)) {
			Holder = IMCharacter;
		}
	}
	else if (auto IMSoul = Cast<AIMSoul>(OtherActor)) {
		if (IMSoul->GetKey(this)) {
			Holder = IMSoul;
		}
	}
}

void AIMKeyLock::SaveRNRItemState()
{
	Saved_Velocity = ProjectileMovement->Velocity;
	Saved_Holder = Holder;
	Saved_RemainingTime = RemainingTime;
}

void AIMKeyLock::PrepRNRItemState()
{
	ProjectileMovement->Velocity = Saved_Velocity;
	Holder = Saved_Holder;
	RemainingTime = Saved_RemainingTime;
}

void AIMKeyLock::OnKeyDrop(FVector Direction)
{
	//example
	ProjectileMovement->Velocity = Direction * 1000;
}

void AIMKeyLock::BeginPlay()
{
	Super::BeginPlay();
}
