
#include "Items/IMBaseItem.h"
#include"Components/BoxComponent.h"
#include"PaperFlipbookComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Player/IMPlayerController.h"
#include"Kismet/GameplayStatics.h"
#include"Debug/MyDebug.h"
AIMBaseItem::AIMBaseItem()
{	
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(Collision);
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Sprite->SetupAttachment(Collision);
	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZDAnimation");
	PaperZDAnimation->InitRenderComponent(Sprite);

}

void AIMBaseItem::BeginPlay()
{
	Super::BeginPlay();
	if (FB_TriggerFinish) {
		Sprite->SetLooping(false);
		Sprite->SetFlipbook(FB_TriggerFinish);
		Sprite->PlayFromStart();
	}
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AIMBaseItem::Trigger);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AIMBaseItem::TriggerFinish);
	auto IMPC = Cast<AIMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(IMPC);
	IMPC->RNRItemRegister(this);
}

void AIMBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIMBaseItem::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FB_Triggered) {
		Sprite->SetLooping(false);
		Sprite->SetFlipbook(FB_Triggered);
		Sprite->PlayFromStart();
	}
}

void AIMBaseItem::TriggerFinish(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (FB_TriggerFinish) {
		Sprite->SetLooping(false);
		Sprite->SetFlipbook(FB_TriggerFinish);
		Sprite->PlayFromStart();
	}
}

void AIMBaseItem::SaveRNRItemState()
{

}
void AIMBaseItem::PrepRNRItemState()
{
}


