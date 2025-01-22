#include "Item.h"
#include "ItemHandle.h"

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
	FRotator VisualizerRotation = PlacementVisualizer->GetComponentRotation();
	VisualizerRotation.Roll = Rotation.Roll;
	VisualizerRotation.Pitch = Rotation.Pitch;
	PlacementVisualizer->SetWorldRotation(VisualizerRotation);
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

