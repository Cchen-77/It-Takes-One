// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonLockComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMAGINE_API UButtonLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UButtonLockComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenFor(float Time);
protected:
	float OpeningTime = 0;
};
