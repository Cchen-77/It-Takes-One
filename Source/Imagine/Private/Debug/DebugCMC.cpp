// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/DebugCMC.h"
#include"Debug/MyDebug.h"
void UDebugCMC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UDebugCMC::PhysFalling(float deltaTime, int32 Iterations)
{
	Super::PhysFalling(deltaTime, Iterations);
}

void UDebugCMC::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	UMyDebug::Message("change");
	if (NewMovementMode == EMovementMode::MOVE_Walking) {
		UMyDebug::Message("to walking");
	}
	Super::SetMovementMode(NewMovementMode, NewCustomMode);
}
