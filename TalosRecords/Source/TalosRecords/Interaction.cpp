#include "Interaction.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

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

	InteractableActor = HitResult.GetActor();
}

void UInteraction::OnPrimaryActionPressed() const
{
	if (ItemHandle->HandlesItem())
	{
		ItemHandle->ReleaseItem();
		return;
	}
	
	if (InteractableActor != nullptr)
	{
		ItemHandle->HandleItem(InteractableActor);
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Interactable actor not found."));
}

void UInteraction::DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const
{
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red);
	DrawDebugSphere( GetWorld(), StartPoint, InteractionRadius, 10, FColor::Red);
	DrawDebugSphere( GetWorld(), EndPoint, InteractionRadius, 10, FColor::Red);
}

