// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMKeyLock.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Components/BoxComponent.h"
#include"Debug/MyDebug.h"
AIMKeyLock::AIMKeyLock()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->SetUpdatedComponent(Collision);
}

void AIMKeyLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Holder) {
		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->SetUpdatedComponent(nullptr);
		if (auto IMCharacter = Cast<AIMCharacter>(Holder)) {
			SetActorLocation(IMCharacter->GetKeySocketLocation());
		}
		else if (auto IMSoul = Cast<AIMSoul>(Holder)) {
			SetActorLocation(IMSoul->GetKeySocketLocation());
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
	if (Holder) return;
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
	if (ProjectileMovement->UpdatedComponent) {
		Saved_bProjectileMoving = true;
	}
	else {
		Saved_bProjectileMoving = false;
	}
	Saved_Velocity = ProjectileMovement->Velocity;
	Saved_Holder = Holder;
	Saved_RemainingTime = RemainingTime;
	Saved_Location = GetActorLocation();
}

void AIMKeyLock::PrepRNRItemState()
{
	if (Saved_bProjectileMoving) {
		ProjectileMovement->SetUpdatedComponent(Collision);
	}
	else {
		ProjectileMovement->SetUpdatedComponent(nullptr);
	}
	ProjectileMovement->Velocity = Saved_Velocity;
	Holder = Saved_Holder;
	RemainingTime = Saved_RemainingTime;
	SetActorLocation(Saved_Location);
}

void AIMKeyLock::OnBeingThrow(FVector Direction)
{
	//example
	Holder = nullptr;
	check(ProjectileMovement);
	ProjectileMovement->SetUpdatedComponent(Collision);
	ProjectileMovement->Velocity = Direction*ThrowingSpeed;
}

void AIMKeyLock::BeginPlay()
{
	Super::BeginPlay();
}
