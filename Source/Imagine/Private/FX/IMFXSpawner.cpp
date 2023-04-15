// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/IMFXSpawner.h"
#include"Engine/DataTable.h"
#include"FX/IMFXActor.h"
#include"PaperFlipbook.h"
#include"Kismet/GameplayStatics.h"
bool UIMFXSpawner::SpawnFX(FName FXName,FVector Location)
{
	if (!FXDataTable.IsValid()) {
		FXDataTable.LoadSynchronous();
	}
	if (!FXDataTable.Get()) {
		return false;
	}
	FFXDataRow* Row = FXDataTable->FindRow<FFXDataRow>(FXName, "FailToFind");
	if (!Row) {
		return false;
	}
	if (!Row->FXSprite.IsValid()) {
		Row->FXSprite.LoadSynchronous();
	}
	if (!Row->FXSprite.Get()) {
		return false;
	}
	FTransform TheTransform;
	TheTransform.SetLocation(Location);
	check(GetWorld());
	auto FXActor = GetWorld()->SpawnActorDeferred<AIMFXActor>(AIMFXActor::StaticClass(),TheTransform);
	check(Row->FXSprite.Get());
	check(FXActor);
	FXActor->SetFXFlipbook(Row->FXSprite.Get());
	UGameplayStatics::FinishSpawningActor(FXActor, TheTransform);
	return true;
}