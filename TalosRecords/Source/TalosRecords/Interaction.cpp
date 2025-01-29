#include "Interaction.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UInteraction::UInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteraction::BeginPlay()
{
	Super::BeginPlay();
	ItemHandle = GetOwner()->FindComponentByClass<UItemHandle>();
}

void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector InteractionStartPoint = GetComponentLocation();
	FVector InteractionEndPoint = InteractionStartPoint + GetForwardVector() * InteractionDistance;
	ScanForInteractableObject(InteractionStartPoint, InteractionEndPoint);

	if (DebugEnabled)
	{
		DrawDebug(InteractionStartPoint, InteractionEndPoint);
	}
}

void UInteraction::ScanForInteractableObject(const FVector& StartPoint, const FVector& EndPoint)
{
	// Stops interaction system if we handle item.
	if (ItemHandle->HasItem())
	{
		InteractableObject = nullptr;
		return;
	}

	// Scans for interactable objects
	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractionRadius);
	FHitResult HitResult;
	GetWorld()->SweepSingleByChannel
	(
		HitResult,
		StartPoint,
		EndPoint,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);

	ResolveInteractableObjectFromHitResult(HitResult);
}

void UInteraction::ResolveInteractableObjectFromHitResult(const FHitResult& HitResult)
{
	InteractableObject = nullptr;

	// The following code tries to find all components on hit actor that implement interactable interface
	AActor* HitActor = HitResult.GetActor();
	if (HitActor != nullptr)
	{
		TArray<UActorComponent*> Components = HitActor->GetComponentsByInterface(UInteractable::StaticClass());

		if (Components.Num() > ALLOWED_INTERACTABLE_COMPONENT_COUNT)
		{
			UE_LOG(LogTemp, Warning, TEXT("Component implements more than one UInteractable! Interaction stopped. Make sure your actor implements only one component with IInteractable interface."));
			return;
		}
		
		for (UActorComponent* Component : Components)
		{
			InteractableObject = Cast<IInteractable>(Component);
			break;
		}
	}
}

FString UInteraction::GetInteractableObjectText() const
{
	return InteractableObject->GetInteractionText();
}

bool UInteraction::HasValidInteractableObject() const
{
	return InteractableObject != nullptr && InteractableObject->Interactable(ItemHandle);
}

void UInteraction::OnPrimaryActionPressed() const
{
	// Handle interaction with item in hand.
	if (ItemHandle->HasItem())
	{
		ItemHandle->PlaceItemToEligiblePlace();
		return;
	}

	// Handle standard interaction with objects.
	if (HasValidInteractableObject())
	{
		InteractableObject->Interact(ItemHandle);
	}
}

void UInteraction::DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const
{
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red);
	DrawDebugSphere( GetWorld(), EndPoint, InteractionRadius, 10, FColor::Red);
}

