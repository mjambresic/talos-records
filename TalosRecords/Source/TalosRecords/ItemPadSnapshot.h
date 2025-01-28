#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemPadSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FItemPadSnapshot
{
	GENERATED_BODY()

	UItem* CurrentItem;
	bool ObjectiveCompleted;

	FItemPadSnapshot() {}

	FItemPadSnapshot(UItem* InCurrentItem)
	{
		CurrentItem = InCurrentItem;
	}

	FItemPadSnapshot(bool InObjectiveCompleted)
	{
		ObjectiveCompleted = InObjectiveCompleted;
	}
	
	FItemPadSnapshot(UItem* InCurrentItem, bool InObjectiveCompleted)
	{
		CurrentItem = InCurrentItem,
		ObjectiveCompleted = InObjectiveCompleted;
	}
};
