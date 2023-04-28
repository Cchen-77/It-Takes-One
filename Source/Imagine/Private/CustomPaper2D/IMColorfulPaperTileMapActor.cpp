// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPaper2D/IMColorfulPaperTileMapActor.h"
#include"PaperTileMapComponent.h"
void AIMColorfulPaperTileMapActor::BeginPlay()
{
	Super::BeginPlay();
	if (Colors.Num() > 0) {
		GetRenderComponent()->SetTileMap(Colors[0]);
		NowColorIdx = 0;
	}
}
void AIMColorfulPaperTileMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NowTime += DeltaTime;
	if (NowTime >= ChangeColorInterval) {
		NowTime -= ChangeColorInterval;
		if (Colors.Num() > 0) {
			NowColorIdx = (NowColorIdx + 1) % Colors.Num();
			GetRenderComponent()->SetTileMap(Colors[NowColorIdx]);
		}
	}
}
