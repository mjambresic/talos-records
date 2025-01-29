#include "ItemHandle.h"
#include "DrawDebugHelpers.h"

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
		AActor* HitActor;

		if (TryHitEligibleItemHolderWithTrace(HitResult, HitActor))
		{
			if (TryResolveItemPlacingOnPad(HitActor))
			{
				return;
			}
			
			ResolveItemPlacingOnNonPadSurface(HitResult);
			return;
		}

		CurrentItem->SetPlacementVisualizerVisible(false);
	}
}

bool UItemHandle::TryHitEligibleItemHolderWithTrace(FHitResult& HitResult, AActor*& HitActor)
{
	UWorld* World = GetWorld();
	FVector TraceStartPoint = Camera->GetComponentLocation();
	FVector TraceEndPoint = TraceStartPoint + Camera->GetForwardVector() * PlacingDistance;
	
	DrawDebugLine(World, TraceStartPoint, TraceEndPoint, FColor::Blue, false);
	bool MainTraceHit = World->LineTraceSingleByChannel(HitResult, TraceStartPoint, TraceEndPoint, ECC_GameTraceChannel2);
	HitActor = HitResult.GetActor();
	CanPlaceItem = HitActor != nullptr && HitActor->Tags.Contains(PLACING_ENABLED_TAG);

	if (CanPlaceItem)
	{
		return true;
	}

	FVector AdditionalTraceBlockPoint = MainTraceHit ? HitResult.Location : TraceEndPoint;

	// Second Level of Tracing, if first one is not successful. Traces n lines from the main trace line downwards.
	int AdditionalTraceCount = 5;
	FVector StepVector = (TraceStartPoint - AdditionalTraceBlockPoint) / (AdditionalTraceCount - 1); // Reverse the order

	for (int i = 0; i < AdditionalTraceCount; i++)
	{
		FVector StartPoint = AdditionalTraceBlockPoint + StepVector * i;
		FVector EndPoint = StartPoint + FVector(0.0f, 0.0f, -PlacingDistance);
		World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_GameTraceChannel2);
		HitActor = HitResult.GetActor();
		CanPlaceItem = HitActor != nullptr && HitActor->Tags.Contains(PLACING_ENABLED_TAG);
		DrawDebugLine(World, StartPoint, EndPoint, FColor::Red, false);

		if (CanPlaceItem)
		{
			return true;
		}
	}

	return false;
}

bool UItemHandle::TryResolveItemPlacingOnPad(const AActor* Actor)
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

void UItemHandle::ResolveItemPlacingOnNonPadSurface(const FHitResult& HitResult)
{
	// Places item visualization on non pad surface that can hold items, additionally sets placement rotation/direction based on the surface impact normal
	FVector ImpactNormal = HitResult.ImpactNormal;
	FVector ItemForwardVector = CurrentItem->GetOwner()->GetActorForwardVector();
	FVector AdjustedForward = FVector::VectorPlaneProject(ItemForwardVector, ImpactNormal).GetSafeNormal();
	FRotator VisualizerRotation = FRotationMatrix::MakeFromXZ(AdjustedForward, ImpactNormal).Rotator();
	UpdatePlacementVisualizer(CanPlaceItem, HitResult.ImpactPoint, VisualizerRotation);
	ItemInteractionText = DROP_INTERACTION_TEXT;
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
