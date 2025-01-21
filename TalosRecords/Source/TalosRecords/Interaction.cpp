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
	DrawDebugLine(GetWorld(), InteractionStartPoint, InteractionEndPoint, FColor::Red, false);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractionRadius);
	FHitResult HitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		InteractionStartPoint,
		InteractionEndPoint,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);

	if (hasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Actor Hit: %s"), *HitActor->GetActorNameOrLabel());
	}
}

