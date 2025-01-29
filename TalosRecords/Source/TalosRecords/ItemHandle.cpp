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
	FVector TraceEndPointMinusItemRadius = TraceStartPoint + Camera->GetForwardVector() * (PlacingDistance - CurrentItem->GetItemRadius());

	bool MainTraceHitSomething = false;
	if (TryLineTrace(HitResult, HitActor, World, TraceStartPoint, TraceEndPointMinusItemRadius, MainTraceHitSomething))
	{
		return true;
	}

	return TryHitEligibleItemHolderWithVerticalTraces(HitResult, HitActor, World, TraceStartPoint, TraceEndPoint, MainTraceHitSomething);
}

bool UItemHandle::TryHitEligibleItemHolderWithVerticalTraces(FHitResult& HitResult, AActor*& HitActor, UWorld* World, const FVector& MainTraceStartPoint, const FVector& MainTraceEndPoint, bool& MainTraceHitSomething)
{
	FVector VerticalTraceBlockPoint = MainTraceHitSomething ? HitResult.Location : MainTraceEndPoint;
	float Distance = FVector::Dist(VerticalTraceBlockPoint, MainTraceStartPoint) - CurrentItem->GetItemRadius();
	FVector Direction = (VerticalTraceBlockPoint - MainTraceStartPoint).GetSafeNormal();
	VerticalTraceBlockPoint = MainTraceStartPoint + Direction * Distance;
	FVector StepVector = (MainTraceStartPoint - VerticalTraceBlockPoint) / (VerticalTraceCount - VERTICAL_TRACE_COUNT_TO_STEPS_MINUEND);

	for (int i = 0; i < VerticalTraceCount; i++)
	{
		FVector StartPoint = VerticalTraceBlockPoint + StepVector * i;
		FVector EndPoint = StartPoint + FVector(NO_OFFSET, NO_OFFSET, -PlacingDistance);
		bool TraceHitSomething = false;
		if (TryLineTrace(HitResult, HitActor, World, StartPoint, EndPoint, TraceHitSomething))
		{
			return true;
		}
	}

	return false;
}

bool UItemHandle::TryLineTrace(FHitResult& HitResult, AActor*& HitActor, UWorld* World, FVector StartPoint, FVector EndPoint, bool& HitSomething)
{
	HitSomething = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_GameTraceChannel2);
	HitActor = HitResult.GetActor();
	CanPlaceItem = HitActor != nullptr && HitActor->Tags.Contains(PLACING_ENABLED_TAG);

	if (DebugEnabled)
	{
		DrawDebugLine(World, StartPoint, EndPoint, FColor::Red, false);
	}
	
	return CanPlaceItem;
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
