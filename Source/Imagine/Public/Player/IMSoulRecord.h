#pragma once
#include"CoreMinimal.h"
#include"IMSoulRecord.generated.h"
USTRUCT(BlueprintType)
struct FIMSoulRecord {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
		FTransform Transform;
	UPROPERTY(BlueprintReadWrite)
		FVector Velocity;
	UPROPERTY(BlueprintReadWrite)
		bool bIsFalling;
	UPROPERTY(BlueprintReadWrite)
		float DeltaTime;
	uint32 ActionBuffer;
	
};