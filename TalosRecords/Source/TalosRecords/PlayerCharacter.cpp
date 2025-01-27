#include "PlayerCharacter.h"

constexpr float GROUND_SPEED_THRESHOLD = 3.0f;

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
	LocationSnapshots.Add(GetOwner()->GetActorLocation());
	RotationSnapshots.Add(GetOwner()->GetActorRotation());
	
	FVector Velocity = MovementComponent->Velocity;
	VelocitySnapshots.Add(Velocity);
	IsFallingSnapshots.Add(MovementComponent->IsFalling());

	float GroundSpeed = Velocity.Size();
	GroundSpeedSnapshots.Add(Velocity.Size2D());

	bool Accelerating = MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
	ShouldMoveSnapshots.Add(Accelerating && GroundSpeed > GROUND_SPEED_THRESHOLD);
}

void UPlayerCharacter::PlaySnapshot(int32 Index)
{
	OnAnimationValueUpdate.Broadcast
	(
		VelocitySnapshots[Index],
		GroundSpeedSnapshots[Index],
		ShouldMoveSnapshots[Index],
		IsFallingSnapshots[Index]
	);

	ThirdPersonPlayerMesh->SetWorldLocation(LocationSnapshots[Index]);
	ThirdPersonPlayerMesh->SetWorldRotation(RotationSnapshots[Index]);
}

void UPlayerCharacter::StartPlaying()
{
	ThirdPersonPlayerMesh->SetVisibility(true, true);
}

void UPlayerCharacter::StopPlaying()
{
	ThirdPersonPlayerMesh->SetVisibility(false, true);
	LocationSnapshots.Empty();
	RotationSnapshots.Empty();
	VelocitySnapshots.Empty();
	GroundSpeedSnapshots.Empty();
	IsFallingSnapshots.Empty();
	ShouldMoveSnapshots.Empty();
}

void UPlayerCharacter::SetMovementComponent(UCharacterMovementComponent* Component)
{
	MovementComponent = Component;
}

void UPlayerCharacter::SetThirdPersonRecordingVisualizer(USceneComponent* Component)
{
	ThirdPersonPlayerMesh = Component;
}