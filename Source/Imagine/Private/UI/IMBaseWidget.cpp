// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMBaseWidget.h"
#include"UI/IMBaseHUD.h"
#include"IMBaseGameInstance.h"
#include"Kismet/GameplayStatics.h"
void UIMBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MyHUD = nullptr;
	MyGI = nullptr;
}

UIMBaseGameInstance* UIMBaseWidget::GetMyGI()
{
	if (!MyGI) {
		MyGI = Cast<UIMBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		check(MyGI);
	}
	return MyGI;
}

AIMBaseHUD* UIMBaseWidget::GetMyHUD()
{
	if (!MyHUD) {
		check(GetOwningPlayer());
		MyHUD = Cast<AIMBaseHUD>(GetOwningPlayer()->GetHUD());
		check(MyHUD);
	}
	return MyHUD;
}
