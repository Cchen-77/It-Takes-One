// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/IMFXActor.h"
#include"PaperFlipbookComponent.h"
AIMFXActor::AIMFXActor()
{
	PrimaryActorTick.bCanEverTick = true;
	FXSprite = CreateDefaultSubobject<UPaperFlipbookComponent>("FXSprite");
	FXSprite->SetLooping(false);
}
void AIMFXActor::BeginPlay()
{
	Super::BeginPlay();
	if (!FXFlipbook) {
		Destroy();
		return;
	}
	FXSprite->SetFlipbook(FXFlipbook);
	FXSprite->OnFinishedPlaying.AddDynamic(this, &AIMFXActor::OnFXFinish);
	FXSprite->PlayFromStart();
}
void AIMFXActor::OnFXFinish()
{
	Destroy();
}
void AIMFXActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIMFXActor::SetFXFlipbook(UPaperFlipbook* FX)
{
	FXFlipbook = FX;
}

