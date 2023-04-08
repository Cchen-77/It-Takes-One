// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomPaper2D/IMBasePaperTileMapActor.h"
#include "IMTransitionPaperTileMapActor.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API AIMTransitionPaperTileMapActor : public AIMBasePaperTileMapActor
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Fade)
		float FadingTime = 0.5;
	float NowTime = 0;
	uint32 FadedDistance = -1;
};
