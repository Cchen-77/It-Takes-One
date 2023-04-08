// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPaper2D/IMTransitionPaperTileMapActor.h"
#include"Debug/MyDebug.h"
#include"PaperTileMapComponent.h"
void AIMTransitionPaperTileMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NowTime += DeltaTime;
	int32 TM_Width, TM_Height, TM_LayerNUM;
	auto TMC = GetRenderComponent();
	check(TMC);
	TMC->GetMapSize(TM_Width, TM_Height, TM_LayerNUM);
	int32 Index = FMath::Floor((NowTime / FadingTime) * (TM_Width + TM_Height - 1)) - 1;
	for (int i = FadedDistance + 1; i <=Index; ++i) {
		for (int j = 0; j < TM_Height; ++j) {
			int k = i - j;
			if (k < 0 || k >= TM_Width) continue;
			for (int l = 0; l < TM_LayerNUM; ++l) {
				TMC->SetTile(k, j, l, FPaperTileInfo());
			}
		}
	}
}

void AIMTransitionPaperTileMapActor::BeginPlay()
{
	Super::BeginPlay();
	auto TMC = GetRenderComponent();
	check(TMC);
	TMC->MakeTileMapEditable();
	FadedDistance = -1;
}
