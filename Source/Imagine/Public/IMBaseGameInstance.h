// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"IMInfoTypes.h"
#include "IMBaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API UIMBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
public:
	bool GetLevelInfo(int idx,FLevelInfo& Info);
	uint32 GetLevelNums() const;
	FName GetNextLevelName();
protected:
	UPROPERTY(EditDefaultsOnly, Category = Levels)
		TArray<FLevelInfo> LevelInfos;
};
