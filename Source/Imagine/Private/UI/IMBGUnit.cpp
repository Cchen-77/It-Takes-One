// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMBGUnit.h"
#include"Debug/MyDebug.h"
void UIMBGUnit::Fadein()
{
	PlayAnimation(FadeinAnim);	
	//SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UIMBGUnit::Fadeout()
{
	PlayAnimation(FadeoutAnim);
	//SetVisibility(ESlateVisibility::Hidden);
}
