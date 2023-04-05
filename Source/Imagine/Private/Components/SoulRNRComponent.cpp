// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SoulRNRComponent.h"
#include"Player/IMPlayerController.h"
#include"Player/IMSoul.h"
#include"Kismet/GameplayStatics.h"
#include"Kismet/KismetMathLibrary.h"
#include"GameFramework/CharacterMovementComponent.h"
void USoulRNRComponent::DoRecording(float DeltaTime)
{
	AddRecord(DeltaTime);
}
void USoulRNRComponent::AddRecord(float DeltaTime)
{
	auto Soul = Cast<AIMSoul>(GetOwner());
	check(Soul);
	FIMSoulRecord Record;
	Record.DeltaTime = DeltaTime;
	Record.Transform = Soul->GetActorTransform();
	auto CMC = Soul->GetCharacterMovement();
	check(CMC);
	Record.Velocity = CMC->Velocity;
	Record.bIsFalling = CMC->IsFalling();
	Record.ActionBuffer = Soul->GetActionBufferCache();
	Records.Enqueue(Record);
	AfterRecord();
}
void USoulRNRComponent::AfterRecord()
{
	auto Soul = Cast<AIMSoul>(GetOwner());
	check(Soul);
	Soul->After_SoulBack();
}
void USoulRNRComponent::ReplayingFinish()
{
	SetRNRState(ERNRState::STATE_None);
	auto Soul = Cast<AIMSoul>(GetOwner());
	check(Soul);
	Soul->DropItem();
	Soul->Destroy();
}
void USoulRNRComponent::DoReplaying(float DeltaTime)
{
	if (Records.IsEmpty()) {
		//guarantee nowdeltatime wiil be 0 next time.
		NowDeltaTime = 0;
		ReplayingFinish();
		return;
	}
	NowDeltaTime += DeltaTime;
	FIMSoulRecord Record;
	Records.Peek(Record);
	while (!Records.IsEmpty() && NowDeltaTime >= Record.DeltaTime) {
		NowDeltaTime -= Record.DeltaTime;
		PrepRecord(Record, 1);
		Records.Pop();
		Records.Peek(Record);
	}
	if (!Records.IsEmpty()) {
		PrepRecord(Record, NowDeltaTime / Record.DeltaTime);
	}
	else {
		NowDeltaTime = 0;
		ReplayingFinish();
		return;
	}
}
void USoulRNRComponent::PrepRecord(FIMSoulRecord Record, float alpha)
{
	FTransform NowTransform = GetOwner()->GetActorTransform();
	FTransform DstTransform = UKismetMathLibrary::TLerp(NowTransform, Record.Transform, alpha);
	auto Soul = Cast<AIMSoul>(GetOwner());
	check(Soul);
	Soul->SetActorTransform(DstTransform);
	Soul->Replaying_Velocity = UKismetMathLibrary::VLerp(Soul->Replaying_Velocity, Record.Velocity, alpha);
	if (alpha == 1) {
		Soul->SetActionBuffer(Record.ActionBuffer);
		Soul->StartAction();
		Soul->Replaying_bIsFalling = Record.bIsFalling;
	}
}