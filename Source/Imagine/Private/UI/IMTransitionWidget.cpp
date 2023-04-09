// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IMTransitionWidget.h"
#include"UI/IMBGUnit.h"
#include"Components/UniformGridPanel.h"
#include"Components/UniformGridSlot.h"
#include"Components/Image.h"
#include"Blueprint/WidgetTree.h"
#include"Debug/MyDebug.h"
bool UIMTransitionWidget::Initialize()
{
	Super::Initialize();
	for (uint32 i = 0; i < GridRows; ++i)
		for (uint32 j = 0; j < GridCollums; ++j) {
			if (BGUnitClass) {
				UIMBGUnit* NewBGUnit = WidgetTree->ConstructWidget<UIMBGUnit>(BGUnitClass);
				if (NewBGUnit) {
					Grid->AddChild(NewBGUnit);
					BGUnits.Add(NewBGUnit);
					auto GridSlot = Cast<UUniformGridSlot>(NewBGUnit->Slot);
					check(GridSlot);
					//flip y axis
					GridSlot->SetRow(GridRows -1 - i);
					GridSlot->SetColumn(j);
					GridSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
					GridSlot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
				}
			}
		}
	return true;
}

void UIMTransitionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (NowTime == BlendingTime) return;
	NowTime += InDeltaTime;
	if (NowTime > BlendingTime) NowTime = BlendingTime;
	uint32 NowDis = FMath::Floor(FMath::Lerp(2, GridCollums + GridRows, NowTime / BlendingTime));
	for (uint32 dis = OldDis + 1; dis <= NowDis; ++dis) {
		for (uint32 i = 1; i < dis&&i<=GridRows; ++i) {
			uint32 j = dis - i;
			if (j > GridCollums) continue;
			if (!bFadeout) {
				BGUnits[(i - 1) * GridCollums + (j - 1)]->Fadein();
			}
			else {
				BGUnits[(i - 1) * GridCollums + (j - 1)]->Fadeout();
			}
		}
	}
	OldDis = NowDis;

}

void UIMTransitionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	NowTime = BlendingTime;
	bFadeout = true;
	OldDis = 1;
}

void UIMTransitionWidget::Fadein()
{
	bFadeout = false;
	NowTime = 0;
	OldDis = 1;
}

void UIMTransitionWidget::FadeOut()
{
	bFadeout = true;
	NowTime = 0;
	OldDis = 1;
}

