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
	ResolveItemPlacingTrace();
}

void UItemHandle::ResolveItemPlacingTrace()
{
	if (HasItem())
	{
		FVector PlacingStartPoint = Camera->GetComponentLocation();
		FVector PlacingEndPoint = PlacingStartPoint + Camera->GetForwardVector() * PlacingDistance;
		FHitResult HitResult;
		CanPlaceItem = GetWorld()->LineTraceSingleByChannel(HitResult, PlacingStartPoint, PlacingEndPoint, ECC_GameTraceChannel2);
		AActor* HitActor = HitResult.GetActor();

		if (TryCheckIfActorIsTaggedToHoldItem(HitActor))
		{
			if (TryCheckIfItemCanBePlacedOnPad(HitActor))
			{
				UpdatePlacementVisualizer(true, CurrentItemPad->GetSocketLocation(), CurrentItemPad->GetSocketRotation());
				return;
			}

			FRotator ImpactRotation = HitResult.ImpactNormal.Rotation();
			ImpactRotation.Yaw = CurrentItem->GetOwner()->GetActorRotation().Yaw;
			UpdatePlacementVisualizer(CanPlaceItem, HitResult.ImpactPoint, ImpactRotation);
			return;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
	}
}

bool UItemHandle::TryCheckIfActorIsTaggedToHoldItem(const AActor* Actor)
{
	// TODO: Replace tag with custom tag system, component?
	CanPlaceItem = CanPlaceItem && Actor != nullptr && Actor->Tags.Contains(FName("CanHoldItem"));
	return CanPlaceItem;
}

bool UItemHandle::TryCheckIfItemCanBePlacedOnPad(AActor* Actor)
{
	CurrentItemPad = Actor->FindComponentByClass<UItemPad>();
	return CurrentItemPad != nullptr && CurrentItemPad->CanPlaceItem();
}

void UItemHandle::UpdatePlacementVisualizer(bool Visible, const FVector& Location, const FRotator& Rotation) const
{
	CurrentItem->SetPlacementVisualizerVisible(Visible);
	CurrentItem->SetPlacementVisualizerLocation(Location);
	CurrentItem->SetPlacementVisualizerRotation(Rotation);
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

bool UItemHandle::HasItem() const
{
	return CurrentItem != nullptr;
}

void UItemHandle::PickUpItem(UItem* Item)
{
	CurrentItem = Item;
	SetItemPhysicsProperties(ECollisionEnabled::NoCollision);
}

void UItemHandle::PlaceItemToEligiblePlace()
{
	if (HasItem() && CanPlaceItem)
	{
		if (CurrentItemPad != nullptr)
		{
			if (CurrentItemPad->CanPlaceItem()) // Places item on pad.
			{
				CurrentItemPad->PlaceItem(CurrentItem);
				PlaceItem(ECollisionEnabled::PhysicsOnly);
				return;
			}
            
			return; // Doesn't place item.
		}
        
		PlaceItem(ECollisionEnabled::QueryAndPhysics); // Places item in world.
	}
}

void UItemHandle::PlaceItem(ECollisionEnabled::Type CollisionType)
{
	CurrentItem->SetPlacementVisualizerVisible(false);
	CurrentItem->SetItemTransformToVisualizerTransform();
	SetItemPhysicsProperties(CollisionType);
	CurrentItem = nullptr;
}


void UItemHandle::SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const
{
	UPrimitiveComponent* InteractableActorPrimitiveComponent = CurrentItem->GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	InteractableActorPrimitiveComponent->SetCollisionEnabled(CollisionType);
}
