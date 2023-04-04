// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMCatchableItem.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Components/BoxComponent.h"
#include"Debug/MyDebug.h"
AIMCatchableItem::AIMCatchableItem()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->SetUpdatedComponent(Collision);
}

void AIMCatchableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Holder) {
		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->SetUpdatedComponent(nullptr);
		if (auto IMCharacter = Cast<AIMCharacter>(Holder)) {
			SetActorLocation(IMCharacter->GetCatchedItemSocketLocation());
		}
		else if (auto IMSoul = Cast<AIMSoul>(Holder)) {
			SetActorLocation(IMSoul->GetCatchedItemSocketLocation());
		}
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else {
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AIMCatchableItem::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Trigger(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (Holder) return;
	if (auto IMCharacter = Cast<AIMCharacter>(OtherActor)) {
		if (IMCharacter->GetItem(this)) {
			Holder = IMCharacter;
		}
	}
	else if (auto IMSoul = Cast<AIMSoul>(OtherActor)) {
		if (IMSoul->GetItem(this)) {
			Holder = IMSoul;
		}
	}
}

void AIMCatchableItem::SaveRNRItemState()
{
	if (ProjectileMovement->UpdatedComponent) {
		Saved_bProjectileMoving = true;
	}
	else {
		Saved_bProjectileMoving = false;
	}
	Saved_Velocity = ProjectileMovement->Velocity;
	Saved_Holder = Holder;
	Saved_Location = GetActorLocation();
}

void AIMCatchableItem::PrepRNRItemState()
{
	if (Saved_bProjectileMoving) {
		ProjectileMovement->SetUpdatedComponent(Collision);
	}
	else {
		ProjectileMovement->SetUpdatedComponent(nullptr);
	}
	ProjectileMovement->Velocity = Saved_Velocity;
	Holder = Saved_Holder;
	SetActorLocation(Saved_Location);
}

void AIMCatchableItem::OnBeingThrow(FVector Direction)
{
	//example
	Holder = nullptr;
	check(ProjectileMovement);
	ProjectileMovement->SetUpdatedComponent(Collision);
	ProjectileMovement->Velocity = Direction*ThrowingSpeed;
}

void AIMCatchableItem::BeginPlay()
{
	Super::BeginPlay();
}
