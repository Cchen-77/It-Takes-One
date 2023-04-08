// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "IMBasePaperTileMapActor.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API AIMBasePaperTileMapActor : public APaperTileMapActor
{
	GENERATED_BODY()
public:
	AIMBasePaperTileMapActor();
protected:
	virtual void BeginPlay() override;
};
