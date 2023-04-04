// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KeyLockComponent.h"
#include"Player/IMCharacter.h"
#include"Items/IMBaseDoor.h"
#include"Items/IMKeyLock.h"
#include"Kismet/GameplayStatics.h"
void UKeyLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto Player = Cast<AIMCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	auto Door = Cast<AIMBaseDoor>(GetOwner());
	check(Door);
	//TODO
	/*if (Player) {
		if (auto Key = Player->GetHoldingKey()) {
			if (Key->KeyID == Door->GetDoorID()) {
				Door->UpdateOpeningState(true);
			}
			else {
				Door->UpdateOpeningState(false);
			}
		}
		else {
			Door->UpdateOpeningState(false);
			return;
		}
	}
	else {
		Door->UpdateOpeningState(false);
	}*/
}
