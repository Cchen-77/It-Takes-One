
#include "Items/IMBaseItem.h"
#include"Components/BoxComponent.h"
#include"PaperFlipbookComponent.h"
#include"PaperZDAnimationComponent.h"
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
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AIMBaseItem::Trigger);
}

void AIMBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIMBaseItem::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


