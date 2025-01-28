#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IObjective.generated.h"

UINTERFACE(Blueprintable)
class UObjective : public UInterface
{
	GENERATED_BODY()
};

class TALOSRECORDS_API IObjective
{
	GENERATED_BODY()

public:
	virtual bool IsCompleted() const = 0;
};
