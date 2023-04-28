// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomPaper2D/IMBasePaperTileMapActor.h"
#include "IMColorfulPaperTileMapActor.generated.h"

/**
 * 
 */
class UPaperTileMap;
UCLASS()
class IMAGINE_API AIMColorfulPaperTileMapActor : public AIMBasePaperTileMapActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Colorful)
		float ChangeColorInterval;
	float NowTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = Colorful)
		TArray<UPaperTileMap*> Colors;
	uint8 NowColorIdx = 0;
};
