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
	return !HoldsItem();
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
	return HoldsItem();
}

FString UItemPad::GetInteractionText()
{
	return CurrentItem->GetInteractionText();
}

bool UItemPad::GetObjectiveCompleted() const
{
	return HoldsItem() || ActivatedByPlayer || OverrideObjectiveCompleted;
}

void UItemPad::SetActivatedByPlayer(bool Activated)
{
	ActivatedByPlayer = Activated;
}

void UItemPad::StartRecording()
{
	PreRecordingSnapshot = FItemPadSnapshot(CurrentItem);
}

void UItemPad::RecordSnapshot()
{
	Snapshots.Add
	(
		FItemPadSnapshot
		(
			GetObjectiveCompleted()
		)
	);
}

void UItemPad::PlaySnapshot(int32 Index)
{
	OverrideObjectiveCompleted = Snapshots[Index].ObjectiveCompleted;
}

void UItemPad::StartPlaying()
{
	ResetToPreRecordingState();
}

void UItemPad::StopPlaying()
{
	OverrideObjectiveCompleted = false;
	Snapshots.Empty();
}

void UItemPad::ResetToPreRecordingState()
{
	CurrentItem = PreRecordingSnapshot.CurrentItem;
}

bool UItemPad::HoldsItem() const
{
	return CurrentItem != nullptr;
}

