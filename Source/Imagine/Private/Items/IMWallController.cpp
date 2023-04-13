// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IMWallController.h"
#include"Items/IMWall.h"
#include"Player/IMCharacter.h"
#include"Player/IMSoul.h"
#include"Kismet/GameplayStatics.h"
#include"PaperFlipbookComponent.h"
void AIMWallController::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetLooping(false);
	if (FB_ControllerSt1) {
		Sprite->SetFlipbook(FB_ControllerSt1);
	}
	IsInSt1 = true;
}
void AIMWallController::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Trigger(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<AIMCharacter>() || OtherActor->IsA<AIMSoul>()) {
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIMWall::StaticClass(), OutActors);
		for (auto OutActor : OutActors) {
			if (auto Wall = Cast<AIMWall>(OutActor)) {
				if (Wall->WallID == WallControllerID) {
					Wall->Move();
				}
			}
		}
		if (IsInSt1) {
			IsInSt1 = false;
			if (FB_ControllerSt2) {
				Sprite->SetFlipbook(FB_ControllerSt2);
			}
		}
		else {
			IsInSt1 = true;
			if (FB_ControllerSt1) {
				Sprite->SetFlipbook(FB_ControllerSt1);
			}
		}
	}
}
