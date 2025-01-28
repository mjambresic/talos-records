#pragma once

#include "CoreMinimal.h"
#include "ItemSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FItemSnapshot
{
	GENERATED_BODY()

	FVector Location;
	FRotator Rotation;
	ECollisionEnabled::Type CollisionEnabledType;
	ECollisionResponse CollisionResponseChannel;

	FItemSnapshot() {}

	FItemSnapshot(const FVector& InLocation, const FRotator& InRotation)
	{
		Location = InLocation;
		Rotation = InRotation;
	}

	FItemSnapshot(const FVector& InLocation, const FRotator& InRotation, ECollisionEnabled::Type InCollisionEnabledType, ECollisionResponse InCollisionResponseChannel)
	{
		Location = InLocation;
		Rotation = InRotation;
		CollisionEnabledType = InCollisionEnabledType;
		CollisionResponseChannel = InCollisionResponseChannel;
	}
};
