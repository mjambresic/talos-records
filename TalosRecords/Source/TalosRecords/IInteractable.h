#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

class UItemHandle;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class TALOSRECORDS_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(UItemHandle* ItemHandle) = 0;
	virtual bool Interactable(UItemHandle* ItemHandle) = 0;
};
