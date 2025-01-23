#include "PuzzleGate.h"
#include "Math/UnrealMathUtility.h"

UPuzzleGate::UPuzzleGate()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPuzzleGate::BeginPlay()
{
	Super::BeginPlay();
	BeginLocation = GetOwner()->GetActorLocation();
	MoveSpeed = FVector::Distance(BeginLocation, BeginLocation + OpenOffset) / OpenDuration;
}

void UPuzzleGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResolveOpenStatus(DeltaTime);
}

void UPuzzleGate::SetOpen(const bool Open)
{
	IsOpen = Open;
}

void UPuzzleGate::ResolveOpenStatus(float DeltaTime) const
{
	if (IsOpen)
	{
		Open(DeltaTime);
	}
	else
	{
		Close(DeltaTime);
	}
}

void UPuzzleGate::Open(float DeltaTime) const
{
	Move(DeltaTime, BeginLocation + OpenOffset);
}

void UPuzzleGate::Close(float DeltaTime) const
{
	Move(DeltaTime, BeginLocation);
}

void UPuzzleGate::Move(float DeltaTime, const FVector& TargetLocation) const
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);
}

