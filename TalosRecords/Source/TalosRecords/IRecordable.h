#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRecordable.generated.h"

UINTERFACE(Blueprintable)
class URecordable : public UInterface
{
	GENERATED_BODY()
};

class TALOSRECORDS_API IRecordable
{
	GENERATED_BODY()

public:
	virtual void AddSnapshot() = 0;
	virtual bool PlaySnapshot(int32 Index) = 0;
};
