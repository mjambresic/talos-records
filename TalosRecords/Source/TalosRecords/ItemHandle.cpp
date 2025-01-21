#include "ItemHandle.h"

UItemHandle::UItemHandle()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemHandle::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UItemHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleItemTransform();

	if (HandlesItem())
	{
		FHitResult HitResult;
		FVector PlacingStartPoint = Camera->GetComponentLocation();
		FVector PlacingEndPoint = PlacingStartPoint + Camera->GetForwardVector() * PlacingDistance;
		bool hasHit = GetWorld()->LineTraceSingleByChannel(HitResult, PlacingStartPoint, PlacingEndPoint, ECC_GameTraceChannel2);
		DrawDebugLine(GetWorld(), PlacingStartPoint, PlacingEndPoint, FColor::Orange);

		CurrentItem->SetPlacementVisualizerVisible(hasHit);
		CurrentItem->SetPlacementVisualizerLocation(HitResult.ImpactPoint);
	}
}

void UItemHandle::HandleItemTransform() const
{
	if (CurrentItem != nullptr)
	{
		CurrentItem->GetOwner()->SetActorLocation(GetComponentLocation());
		HandleItemRotation();
	}
}

void UItemHandle::HandleItemRotation() const
{
	FRotator ItemRotation = FRotator
	(
		Camera->GetComponentRotation().Pitch + ItemRotationOffset.X,
		Camera->GetComponentRotation().Yaw + ItemRotationOffset.Z,
		Camera->GetComponentRotation().Roll + ItemRotationOffset.Y
	);
		
	CurrentItem->GetOwner()->SetActorRotation(ItemRotation);
}

bool UItemHandle::HandlesItem() const
{
	return CurrentItem != nullptr;
}

void UItemHandle::HandleItem(UItem* Item)
{
	CurrentItem = Item;
	SetItemPhysicsProperties(ECollisionEnabled::NoCollision);
}

void UItemHandle::ReleaseItem()
{
	if (HandlesItem())
	{
		SetItemPhysicsProperties(ECollisionEnabled::QueryAndPhysics);
		CurrentItem->SetPlacementVisualizerVisible(false);
		CurrentItem = nullptr;
	}
}

void UItemHandle::SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const
{
	UPrimitiveComponent* InteractableActorPrimitiveComponent = CurrentItem->GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	InteractableActorPrimitiveComponent->SetCollisionEnabled(CollisionType);
}
