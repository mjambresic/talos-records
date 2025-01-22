#include "Item.h"
#include "ItemHandle.h"
#include "Components/ShapeComponent.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"

UItem::UItem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItem::BeginPlay()
{
	Super::BeginPlay();
}

void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItem::SetPlacementVisualizerLocation(FVector Location) const
{
	Location.Z += BaseOffset;
	PlacementVisualizer->SetWorldLocation(Location);
}

void UItem::SetPlacementVisualizerRotation(const FRotator& Rotation) const
{
	PlacementVisualizer->SetWorldRotation(Rotation);
}

void UItem::SetItemTransformToVisualizerTransform() const
{
	GetOwner()->SetActorLocation(PlacementVisualizer->GetComponentLocation());
	GetOwner()->SetActorRotation(PlacementVisualizer->GetComponentRotation());
}

void UItem::Interact(UItemHandle* ItemHandle)
{
	ItemHandle->PickUpItem(this);
}

void UItem::SetCollisionEnabled(ECollisionEnabled::Type CollisionType) const
{
	Collider->SetCollisionEnabled(CollisionType);
}

void UItem::SetInteractionCollisionResponse(const ECollisionResponse Response) const
{
	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, Response);
	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel2, Response);
}

bool UItem::Interactable(UItemHandle* ItemHandle)
{
	return !ItemHandle->HasItem();
}

void UItem::SetPlacementVisualizerVisible(bool Visible) const
{
	PlacementVisualizer->SetVisibility(Visible, true);
}

void UItem::SetPlacementVisualizer(USceneComponent* Visualizer)
{
	PlacementVisualizer = Visualizer;
}

void UItem::SetCollider(UShapeComponent* ShapeCollider)
{
	Collider = ShapeCollider;
}

