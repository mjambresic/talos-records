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

	if (HasItem())
	{
		FVector PlacingStartPoint = Camera->GetComponentLocation();
		FVector PlacingEndPoint = PlacingStartPoint + Camera->GetForwardVector() * PlacingDistance;
		FHitResult HitResult;
		HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, PlacingStartPoint, PlacingEndPoint, ECC_GameTraceChannel2);

		if (HasHit)
		{
			// TODO: Tag with custom component instead of string tags.
			HasHit = HitResult.GetActor()->Tags.Contains(FName("CanHoldItem"));
		}

		if (HasHit)
		{
			CurrentItemPad = HitResult.GetActor()->FindComponentByClass<UItemPad>();
			if (CurrentItemPad != nullptr)
			{
				HasHit = CurrentItemPad->CanPlaceItem(); 
				if (!HasHit)
				{
					CurrentItem->SetPlacementVisualizerVisible(false);
					return;
				}
				
				CurrentItem->SetPlacementVisualizerVisible(true);
				CurrentItem->SetPlacementVisualizerLocation(CurrentItemPad->GetSocketLocation());
				CurrentItem->SetPlacementVisualizerRotation(CurrentItemPad->GetSocketRotation());
				return;
			}
		}

		CurrentItem->SetPlacementVisualizerVisible(HasHit);
		CurrentItem->SetPlacementVisualizerLocation(HitResult.ImpactPoint);
		CurrentItem->SetPlacementVisualizerRotation(HitResult.ImpactNormal.Rotation());
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
	if (HasItem() && HasHit)
	{
		if (CurrentItemPad != nullptr)
		{
			if (CurrentItemPad->CanPlaceItem())
			{
				CurrentItemPad->PlaceItem(CurrentItem);
				PlaceItem(ECollisionEnabled::PhysicsOnly);
				return;
			}
            
			return; // Doesn't place item.
		}
        
		PlaceItem(ECollisionEnabled::QueryAndPhysics);
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
