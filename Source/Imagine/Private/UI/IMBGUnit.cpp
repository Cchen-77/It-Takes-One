// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMBGUnit.h"

void UIMBGUnit::Fadein()
{
	PlayAnimation(FadeinAnim);
}

void UIMBGUnit::Fadeout()
{
	PlayAnimation(FadeoutAnim);
}
