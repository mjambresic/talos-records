#pragma once

#include "CoreMinimal.h"
#include "ItemPadSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FItemPadSnapshot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool ObjectiveCompleted;

	FItemPadSnapshot() {}

	FItemPadSnapshot(bool InObjectiveCompleted)
	{
		ObjectiveCompleted = InObjectiveCompleted;
	}
};
