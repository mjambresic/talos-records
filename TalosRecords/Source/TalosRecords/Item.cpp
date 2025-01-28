#include "Item.h"
#include "ItemHandle.h"
#include "Components/ShapeComponent.h"

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
	ItemHandle->TakeItem(this);
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

FString UItem::GetInteractionText()
{
	return InteractionText;
}

void UItem::StartRecording()
{
	PreRecordingSnapshot.Location = GetOwner()->GetActorLocation();
	PreRecordingSnapshot.Rotation = GetOwner()->GetActorRotation();
	PreRecordingSnapshot.CollisionEnabledType = Collider->GetCollisionEnabled();
	PreRecordingSnapshot.CollisionResponseChannel = Collider->GetCollisionResponseToChannel(ECC_GameTraceChannel1);
}

void UItem::RecordSnapshot()
{
	Snapshots.Add
	(
		FItemSnapshot
		(
			GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation()
		)
	);
}

void UItem::PlaySnapshot(int32 Index)
{
	FItemSnapshot Snapshot = Snapshots[Index];
	RecordingVisualizer->SetWorldLocation(Snapshot.Location);
	RecordingVisualizer->SetWorldRotation(Snapshot.Rotation);
}

void UItem::StartPlaying()
{
	SetRecordingVisualizerVisible(true);
	ResetToPreRecordingState();
}

void UItem::StopPlaying()
{
	SetRecordingVisualizerVisible(false);
	Snapshots.Empty();
}

void UItem::ResetToPreRecordingState() const
{
	GetOwner()->SetActorLocation(PreRecordingSnapshot.Location);
	GetOwner()->SetActorRotation(PreRecordingSnapshot.Rotation);
	SetCollisionEnabled(PreRecordingSnapshot.CollisionEnabledType);
	SetInteractionCollisionResponse(PreRecordingSnapshot.CollisionResponseChannel);
}

void UItem::SetPlacementVisualizerVisible(bool Visible) const
{
	PlacementVisualizer->SetVisibility(Visible, true);
}

void UItem::SetPlacementVisualizer(USceneComponent* Visualizer)
{
	PlacementVisualizer = Visualizer;
}

void UItem::SetRecordingVisualizerVisible(bool Visible) const
{
	RecordingVisualizer->SetVisibility(Visible, true);
}

void UItem::SetRecordingVisualizer(USceneComponent* Visualizer)
{
	RecordingVisualizer = Visualizer;
}

void UItem::SetCollider(UShapeComponent* ShapeCollider)
{
	Collider = ShapeCollider;
}