// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMWall.h"
#include"Player/IMSoul.h"
#include"Debug/MyDebug.h"
void AIMWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsSrc2Dst) {
		if (NowTime == BlendingTime) return;
		NowTime += DeltaTime;
		if (NowTime > BlendingTime) {
			NowTime = BlendingTime;
		}
	}
	else {
		if (NowTime == 0) return;
		NowTime -= DeltaTime;
		if (NowTime < 0) {
			NowTime = 0;
		}
	}
	FVector RealLocation = FMath::Lerp(SrcLocation, DstLocation, NowTime / BlendingTime);
	SetActorLocation(RealLocation);
}

void AIMWall::Move()
{
	bIsSrc2Dst = !bIsSrc2Dst;
}

void AIMWall::BeginPlay()
{
	Super::BeginPlay();
	bIsSrc2Dst = false;
	SrcLocation = GetActorLocation();
	check(BlendingTime > 0)
}

void AIMWall::SaveRNRItemState()
{
	Saved_Location = GetActorLocation();
	Saved_bIsSrc2Dst = bIsSrc2Dst;
	Saved_NowTime = NowTime;
}

void AIMWall::PrepRNRItemState()
{
	SetActorLocation(Saved_Location);
	bIsSrc2Dst = Saved_bIsSrc2Dst;
	NowTime = Saved_NowTime;
}

void AIMWall::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Trigger(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
