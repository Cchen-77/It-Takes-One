// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KeyLockComponent.h"
#include"Player/IMCharacter.h"
#include"Items/IMBaseDoor.h"
#include"Items/ImKeyLock.h"
#include"Kismet/GameplayStatics.h"
#include"Debug/MyDebug.h"
void UKeyLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto Player = Cast<AIMCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto Door = Cast<AIMBaseDoor>(GetOwner());
	check(Door);
	if (Player) {
		if (auto Key = Cast<AIMKeyLock>(Player->GetCatchedItem())) {
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
	}
}
