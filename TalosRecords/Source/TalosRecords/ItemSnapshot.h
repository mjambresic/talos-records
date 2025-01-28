#pragma once

#include "CoreMinimal.h"
#include "ItemSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FItemSnapshot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;

	FItemSnapshot() {}

	FItemSnapshot(const FVector& InLocation, const FRotator& InRotation)
	{
		Location = InLocation;
		Rotation = InRotation;
	}
};
