// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMBaseHUD.h"
#include"UI/IMMainMenuWidget.h"
#include"UI/IMTransitionWidget.h"
void AIMBaseHUD::Transition_Fadein()
{

}
void AIMBaseHUD::Transition_Fadeout()
{
	if (!TransitionWidget) {
		check(TransitionWidgetClass);
		TransitionWidget = CreateWidget<UIMTransitionWidget>(GetOwningPlayerController(), TransitionWidgetClass);
	}

}

void AIMBaseHUD::BeginPlay()
{
	Super::BeginPlay();
}
