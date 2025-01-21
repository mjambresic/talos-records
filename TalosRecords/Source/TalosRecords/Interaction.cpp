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

void UInteraction::DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const
{
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false);
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

void UInteraction::OnInteractActionPressed() const
{
	if (InteractableActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor Interaction: %s"), *InteractableActor->GetActorNameOrLabel());
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Interactable actor not found."));
}

