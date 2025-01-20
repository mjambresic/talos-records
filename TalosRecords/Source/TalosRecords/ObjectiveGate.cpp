#include "ObjectiveGate.h"
#include "Math/UnrealMathUtility.h"

UObjectiveGate::UObjectiveGate()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObjectiveGate::BeginPlay()
{
	Super::BeginPlay();
	BeginLocation = GetOwner()->GetActorLocation();
	MoveSpeed = FVector::Distance(BeginLocation, BeginLocation + OpenOffset) / OpenDuration;
}

void UObjectiveGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResolveObjectivesCleared(DeltaTime);
}

void UObjectiveGate::ResolveObjectivesCleared(float DeltaTime) const
{
	if (objectivesCleared)
	{
		Open(DeltaTime);
	}
	else
	{
		Close(DeltaTime);
	}
}

void UObjectiveGate::Open(float DeltaTime) const
{
	Move(DeltaTime, BeginLocation + OpenOffset);
}

void UObjectiveGate::Close(float DeltaTime) const
{
	Move(DeltaTime, BeginLocation);
}

void UObjectiveGate::Move(float DeltaTime, const FVector& TargetLocation) const
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);
}

