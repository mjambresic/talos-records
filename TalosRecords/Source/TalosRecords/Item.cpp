#include "Item.h"

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
	PlacementVisualizer->SetWorldLocation(Location);
}

void UItem::SetPlacementVisualizerVisible(bool Visible) const
{
	PlacementVisualizer->SetVisibility(Visible, true);
}

void UItem::SetPlacementVisualizer(USceneComponent* Visualizer)
{
	PlacementVisualizer = Visualizer;
}

