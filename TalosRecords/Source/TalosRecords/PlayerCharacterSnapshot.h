#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCharacterSnapshot
{
	GENERATED_BODY()

	FVector Location;
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly)
	FVector Velocity;
    
	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool ShouldMove;

	UPROPERTY(BlueprintReadOnly)
	bool IsFalling;

	FPlayerCharacterSnapshot() {}

	FPlayerCharacterSnapshot(const FVector& InLocation, const FRotator& InRotation, const FVector& InVelocity, float InGroundSpeed, bool InShouldMove, bool InIsFalling)
	{
		Location = InLocation;
		Rotation = InRotation;
		Velocity = InVelocity;
		GroundSpeed = InGroundSpeed;
		ShouldMove = InShouldMove;
		IsFalling = InIsFalling;
	}
};
