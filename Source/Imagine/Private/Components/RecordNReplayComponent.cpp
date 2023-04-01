// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RecordNReplayComponent.h"
#include"Player/IMPlayerController.h"
#include"Player/RecordNReplayManager.h"
#include"Kismet/GameplayStatics.h"
// Sets default values for this component's properties
URecordNReplayComponent::URecordNReplayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
}
void URecordNReplayComponent::BeginPlay()
{
	Super::BeginPlay();
}
void URecordNReplayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	switch (GetRNRState()) {
		case ERNRState::STATE_None:
			break;
		case ERNRState::STATE_Recording:
			DoRecording(DeltaTime);
			break;
		case ERNRState::STATE_Replaying:
			DoReplaying(DeltaTime);
			break;
	}
}

void URecordNReplayComponent::DoRecording(float DeltaTime)
{
	
}
void URecordNReplayComponent::DoReplaying(float DeltaTime)
{

}

ERNRState URecordNReplayComponent::GetRNRState() const
{
	return RNRState;
}

void URecordNReplayComponent::SetRNRState(ERNRState State)
{
	RNRState = State;
}

