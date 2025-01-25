#include "ItemHandle.h"

static const FString DROP_INTERACTION_TEXT = TEXT("Drop");
static const FString PLACE_INTERACTION_TEXT = TEXT("Place");

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
		FHitResult HitResult;
		CanPlaceItem = ItemPlacingTrace(HitResult);
		AActor* HitActor = HitResult.GetActor();

		if (TryCheckIfActorIsTaggedToHoldItem(HitActor))
		{
			if (TryResolveVisualizationOnPad(HitActor))
			{
				return;
			}

			ResolveItemPlacingOnNonPadSurface(HitResult);
			return;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
	}
}

bool UItemHandle::ItemPlacingTrace(FHitResult& HitResult) const
{
	FVector PlacingStartPoint = Camera->GetComponentLocation();
	FVector PlacingEndPoint = PlacingStartPoint + Camera->GetForwardVector() * PlacingDistance;
	return GetWorld()->LineTraceSingleByChannel(HitResult, PlacingStartPoint, PlacingEndPoint, ECC_GameTraceChannel2);
}

bool UItemHandle::TryCheckIfActorIsTaggedToHoldItem(const AActor* Actor)
{
	// TODO: Replace tag with custom tag system, component?
	CanPlaceItem = CanPlaceItem && Actor != nullptr && Actor->Tags.Contains(FName("CanHoldItem"));
	return CanPlaceItem;
}

bool UItemHandle::TryResolveVisualizationOnPad(const AActor* Actor)
{
	CurrentItemPad = Actor->FindComponentByClass<UItemPad>();
	if (CurrentItemPad != nullptr)
	{
		if (CurrentItemPad->CanPlaceItem())
		{
			UpdatePlacementVisualizer(true, CurrentItemPad->GetSocketLocation(), CurrentItemPad->GetSocketRotation());
			ItemInteractionText = PLACE_INTERACTION_TEXT;
			return true;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
		CanPlaceItem = false;
		return true;
	}

	return false;
}

void UItemHandle::ResolveItemPlacingOnNonPadSurface(const FHitResult& HitResult) const
{
	// Places item visualization on non pad surface that can hold items, additionally sets placement rotation/direction based on the surface impact normal
	FVector ImpactNormal = HitResult.ImpactNormal;
	FVector ItemForwardVector = CurrentItem->GetOwner()->GetActorForwardVector();
	FVector AdjustedForward = FVector::VectorPlaneProject(ItemForwardVector, ImpactNormal).GetSafeNormal();
	FRotator VisualizerRotation = FRotationMatrix::MakeFromXZ(AdjustedForward, ImpactNormal).Rotator();
	UpdatePlacementVisualizer(CanPlaceItem, HitResult.ImpactPoint, VisualizerRotation);
}

void UItemHandle::UpdatePlacementVisualizer(bool Visible, const FVector& Location, const FRotator& Rotation) const
{
	CurrentItem->SetPlacementVisualizerVisible(Visible);
	CurrentItem->SetPlacementVisualizerLocation(Location);
	CurrentItem->SetPlacementVisualizerRotation(Rotation);
}

bool UItemHandle::GetCanPlaceItem() const
{
	return HasItem() && CanPlaceItem;
}

FString UItemHandle::GetItemInteractionText() const
{
	return ItemInteractionText;
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

void UItemHandle::TakeItem(UItem* Item)
{
	CurrentItem = Item;
	SetItemPhysicsProperties(ECollisionEnabled::NoCollision);
}

void UItemHandle::PlaceItemToEligiblePlace()
{
	if (HasItem() && CanPlaceItem)
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
