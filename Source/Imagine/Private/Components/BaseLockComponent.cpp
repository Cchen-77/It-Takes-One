// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseLockComponent.h"
#include"Items/IMBaseDoor.h"
UBaseLockComponent::UBaseLockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
}
void UBaseLockComponent::BeginPlay()
{
	Super::BeginPlay();	
	auto Door = Cast<AIMBaseDoor>(GetOwner());
	check(Door);
	Door->RegisterLockComponent(this);
}
void UBaseLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseLockComponent::SaveState()
{
}

void UBaseLockComponent::PrepState()
{
}

