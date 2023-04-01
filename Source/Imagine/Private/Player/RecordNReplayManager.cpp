// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RecordNReplayManager.h"

void URecordNReplayManager::SetRNRState(ERNRState State)
{
	RNRState = State;
}

ERNRState URecordNReplayManager::GetRNRState() const
{
	return RNRState;
}
