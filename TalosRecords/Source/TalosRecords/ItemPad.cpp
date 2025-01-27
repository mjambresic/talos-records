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
	return HasItemPlaced() || CompletedOnRecord;
}

void UItemPad::RecordSnapshot()
{
	ObjectiveCompletedSnapshots.Add(HasItemPlaced());
}

void UItemPad::PlaySnapshot(int32 Index)
{
	CompletedOnRecord = ObjectiveCompletedSnapshots[Index];
}

void UItemPad::StopPlaying()
{
	CompletedOnRecord = false;
	ObjectiveCompletedSnapshots.Empty();
}

bool UItemPad::HasItemPlaced() const
{
	return CurrentItem != nullptr;
}

