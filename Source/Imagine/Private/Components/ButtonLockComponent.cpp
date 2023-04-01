// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ButtonLockComponent.h"
#include"Items/IMBaseDoor.h"
#include"Debug/MyDebug.h"
UButtonLockComponent::UButtonLockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
}

void UButtonLockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UButtonLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OpeningTime = OpeningTime - DeltaTime;
	if (OpeningTime < 0)
	{
		OpeningTime = 0;
	}
	auto Door = Cast<AIMBaseDoor>(GetOwner());
	check(Door);
	Door->UpdateOpeningState(OpeningTime != 0);
}

void UButtonLockComponent::OpenFor(float Time)
{
	OpeningTime += Time;
}

