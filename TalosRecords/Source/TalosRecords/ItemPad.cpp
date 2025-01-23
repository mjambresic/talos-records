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
	ItemHandle->PickUpItem(CurrentItem);
	CurrentItem = nullptr;
}

bool UItemPad::Interactable(UItemHandle* ItemHandle)
{
	return HasItemPlaced();
}

bool UItemPad::IsCompleted()
{
	return HasItemPlaced();
}

bool UItemPad::HasItemPlaced() const
{
	return CurrentItem != nullptr;
}
