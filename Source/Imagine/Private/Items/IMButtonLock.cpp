// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMButtonLock.h"
#include"Items/IMBaseDoor.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Components/ButtonLockComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Debug/MyDebug.h"
void AIMButtonLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AIMButtonLock::BeginPlay()
{
	Super::BeginPlay();
}
void AIMButtonLock::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Trigger(OverlappedComponent,OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);
	if (OtherActor->IsA(AIMSoul::StaticClass())|| OtherActor->IsA(AIMCharacter::StaticClass())) {
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),AIMBaseDoor::StaticClass(), OutActors);
		for (auto OutActor : OutActors) {
			if (auto Door = Cast<AIMBaseDoor>(OutActor)) {
				if (Door->GetDoorID() == LockID) {
					if (auto BLC = Cast<UButtonLockComponent>(Door->GetComponentByClass(UButtonLockComponent::StaticClass()))) {
						BLC->OpenFor(OpenTime);
					}
				}
			}
		}
	}
}
