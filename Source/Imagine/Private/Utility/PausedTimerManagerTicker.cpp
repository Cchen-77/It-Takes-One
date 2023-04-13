#include "Utility/PausedTimerManagerTicker.h"
APausedTimerManagerTicker::APausedTimerManagerTicker()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
}
void APausedTimerManagerTicker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld() && GetWorld()->IsPaused()) {
		GetWorld()->GetTimerManager().Tick(DeltaTime);
	}
}

