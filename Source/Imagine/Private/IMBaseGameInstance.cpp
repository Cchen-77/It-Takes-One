// Fill out your copyright notice in the Description page of Project Settings.


#include "IMBaseGameInstance.h"
#include"Kismet/GameplayStatics.h"
#include"GameFramework/GameUserSettings.h"
#include"Debug/MyDebug.h"
void UIMBaseGameInstance::Init()
{
	Super::Init();
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->SetFrameRateLimit(60);
	Settings->SetFullscreenMode(EWindowMode::Windowed);
	Settings->SetScreenResolution(FIntPoint(1280, 720));
	Settings->ApplySettings(false);
}

bool UIMBaseGameInstance::GetLevelInfo(int idx, FLevelInfo& Info)
{
	if (idx < 0 || idx >= LevelInfos.Num()) return false;
	Info = LevelInfos[idx];
	return true;
}

uint32 UIMBaseGameInstance::GetLevelNums() const
{
	return LevelInfos.Num();
}

FName UIMBaseGameInstance::GetNextLevelName()
{
	uint8 curidx = 0;
	FString TheName = WorldContext->World()->GetMapName();
	TheName.RemoveFromStart(WorldContext->World()->StreamingLevelsPrefix);
	FName CurLevelName = *TheName;
	for (; curidx != LevelInfos.Num(); ++curidx) {
		if (LevelInfos[curidx].LevelName == CurLevelName)
			break;
	}
	check(curidx != LevelInfos.Num());
	if (curidx + 1 == LevelInfos.Num()) {
		return "NULL";
	}

	return LevelInfos[curidx + 1].LevelName;
}
