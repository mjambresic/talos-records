#include "PlayerCharacter.h"

UPlayerCharacter::UPlayerCharacter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerCharacter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerCharacter::RecordSnapshot()
{
	FVector Velocity = MovementComponent->Velocity;
	float GroundSpeed = Velocity.Size();
	bool Accelerating = MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
	
	Snapshots.Add
	(
		FPlayerCharacterSnapshot
		(
			GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation(),
			MovementComponent->Velocity,
			MovementComponent->Velocity.Size2D(),
			Accelerating && GroundSpeed > GROUND_SPEED_THRESHOLD,
			MovementComponent->IsFalling()
		)
	);
}

void UPlayerCharacter::PlaySnapshot(int32 Index)
{
	FPlayerCharacterSnapshot Snapshot = Snapshots[Index];
	OnPlaySnapshotAnimationValues.Broadcast
	(
		Snapshot.Velocity,
		Snapshot.GroundSpeed,
		Snapshot.ShouldMove,
		Snapshot.IsFalling
	);

	ThirdPersonPlayerMesh->SetWorldLocation(Snapshot.Location);
	ThirdPersonPlayerMesh->SetWorldRotation(Snapshot.Rotation);
}

void UPlayerCharacter::StartPlaying()
{
	ThirdPersonPlayerMesh->SetVisibility(true, true);
}

void UPlayerCharacter::StopPlaying()
{
	ThirdPersonPlayerMesh->SetVisibility(false, true);
	Snapshots.Empty();
}

void UPlayerCharacter::SetMovementComponent(UCharacterMovementComponent* Component)
{
	MovementComponent = Component;
}

void UPlayerCharacter::SetThirdPersonRecordingVisualizer(USceneComponent* Component)
{
	ThirdPersonPlayerMesh = Component;
}