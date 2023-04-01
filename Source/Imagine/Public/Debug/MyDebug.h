#pragma once
#include"CoreMinimal.h"
#include"Engine.h"
class UMyDebug{
public:
	static void Message(FString s) {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, s);
	}
};