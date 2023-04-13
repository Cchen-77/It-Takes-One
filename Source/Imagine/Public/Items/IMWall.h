// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItem.h"
#include "IMWall.generated.h"

/**
 * 
 */
UCLASS()
class IMAGINE_API AIMWall : public AIMBaseItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void Move();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wall)
		int WallID;
protected:
	virtual void BeginPlay() override;
	virtual void SaveRNRItemState() override;
	virtual void PrepRNRItemState() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Wall)
	float BlendingTime = 1;
	float NowTime = 0;
	FVector SrcLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wall)
	FVector DstLocation;
	bool bIsSrc2Dst;

	FVector Saved_Location;
	bool Saved_bIsSrc2Dst;
	float Saved_NowTime;

};
