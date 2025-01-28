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
	virtual void StartRecording() = 0;
	virtual void RecordSnapshot() = 0;
	virtual void PlaySnapshot(int32 Index) = 0;
	virtual void StartPlaying() = 0;
	virtual void StopPlaying() = 0;
};
