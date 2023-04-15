// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include"Engine/DataTable.h"
#include "IMFXSpawner.generated.h"

/**
 * 
 */
class UDataTable;
class UPaperFlipbook;
USTRUCT(BlueprintType)
struct FFXDataRow :public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
		TSoftObjectPtr<UPaperFlipbook> FXSprite;
};
UCLASS(Blueprintable,BlueprintType)
class IMAGINE_API UIMFXSpawner : public UObject
{
	GENERATED_BODY()
public:
	bool SpawnFX(FName FXName,FVector Location);
protected:
	UPROPERTY(EditDefaultsOnly, Category = FX)
		TSoftObjectPtr<UDataTable> FXDataTable;
};
