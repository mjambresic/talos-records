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
		HitActorCanHoldItem = GetWorld()->LineTraceSingleByChannel(HitResult, PlacingStartPoint, PlacingEndPoint, ECC_GameTraceChannel2);
		AActor* HitActor = HitResult.GetActor();

		if (TryCheckIfActorIsTaggedToHoldItem(HitActor))
		{
			if (TryResolveVisualizationOnPad(HitActor))
			{
				return;
			}
			
			// Places visualization on non pad surface that can hold items.
			FRotator ImpactRotation = HitResult.ImpactNormal.Rotation();
			ImpactRotation.Yaw = CurrentItem->GetOwner()->GetActorRotation().Yaw;
			UpdatePlacementVisualizer(HitActorCanHoldItem, HitResult.ImpactPoint, ImpactRotation);
			return;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
	}
}

bool UItemHandle::TryCheckIfActorIsTaggedToHoldItem(const AActor* Actor)
{
	// TODO: Replace tag with custom tag system, component?
	HitActorCanHoldItem = HitActorCanHoldItem && Actor != nullptr && Actor->Tags.Contains(FName("CanHoldItem"));
	return HitActorCanHoldItem;
}

bool UItemHandle::TryResolveVisualizationOnPad(const AActor* Actor)
{
	CurrentItemPad = Actor->FindComponentByClass<UItemPad>();
	if (CurrentItemPad != nullptr)
	{
		if (CurrentItemPad->CanPlaceItem())
		{
			UpdatePlacementVisualizer(true, CurrentItemPad->GetSocketLocation(), CurrentItemPad->GetSocketRotation());
			return true;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
		HitActorCanHoldItem = false;
		return true;
	}

	return false;
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
	if (HasItem() && HitActorCanHoldItem)
	{
		SetItemPhysicsProperties(ECollisionEnabled::QueryAndPhysics);

		if (CurrentItemPad != nullptr && CurrentItemPad->CanPlaceItem())
		{
			CurrentItemPad->PlaceItem(CurrentItem);
			CurrentItem->SetInteractionCollisionResponse(ECR_Ignore);
			PlaceItem();
			return;
		}

		CurrentItem->SetInteractionCollisionResponse(ECR_Block);
		PlaceItem();
	}
}

void UItemHandle::PlaceItem()
{
	CurrentItem->SetPlacementVisualizerVisible(false);
	CurrentItem->SetItemTransformToVisualizerTransform();
	CurrentItem = nullptr;
}

void UItemHandle::SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const
{
	CurrentItem->SetCollisionEnabled(CollisionType);
}
