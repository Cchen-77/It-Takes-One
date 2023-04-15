#pragma once
#include"CoreMinimal.h"
#include"IMInfoTypes.generated.h"
USTRUCT(BlueprintType)
struct FLevelInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
		FName LevelName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int Stars;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bLock = false;
};
