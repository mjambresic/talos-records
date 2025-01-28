#include "ItemPad.h"

#include "ItemHandle.h"

UItemPad::UItemPad()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemPad::BeginPlay()
{
	Super::BeginPlay();
}

void UItemPad::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemPad::SetItemSocket(USceneComponent* ItemSocketSceneComponent)
{
	ItemSocket = ItemSocketSceneComponent;
}

FVector UItemPad::GetSocketLocation() const
{
	return ItemSocket->GetComponentLocation();
}

FRotator UItemPad::GetSocketRotation() const
{
	return ItemSocket->GetComponentRotation();
}

bool UItemPad::CanPlaceItem() const
{
	return !HasItemPlaced();
}

bool UItemPad::CanTakeItem() const
{
	return HasItemPlaced();
}

void UItemPad::PlaceItem(UItem* Item)
{
	CurrentItem = Item;
}

void UItemPad::Interact(UItemHandle* ItemHandle)
{
	ItemHandle->TakeItem(CurrentItem);
	CurrentItem = nullptr;
}

bool UItemPad::Interactable(UItemHandle* ItemHandle)
{
	return HasItemPlaced();
}

FString UItemPad::GetInteractionText()
{
	return CurrentItem->GetInteractionText();
}

bool UItemPad::IsCompleted()
{
	return HasItemPlaced() || ObjectiveCompletedBySnapshot;
}

void UItemPad::RecordSnapshot()
{
	Snapshots.Add
	(
		FItemPadSnapshot (HasItemPlaced())
	);
}

void UItemPad::PlaySnapshot(int32 Index)
{
	ObjectiveCompletedBySnapshot = Snapshots[Index].ObjectiveCompleted;
}

void UItemPad::StopPlaying()
{
	ObjectiveCompletedBySnapshot = false;
	Snapshots.Empty();
}

bool UItemPad::HasItemPlaced() const
{
	return CurrentItem != nullptr;
}

