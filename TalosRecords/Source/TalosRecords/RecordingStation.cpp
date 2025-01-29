#include "RecordingStation.h"

URecordingStation::URecordingStation()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URecordingStation::BeginPlay()
{
	Super::BeginPlay();
}

// Remember that this component may have custom Tick Interval set, to limit snapshotting performance impact.
void URecordingStation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResolveStates(DeltaTime);
}

void URecordingStation::ResolveStates(float DeltaTime)
{
	if (Recording)
	{
		ResolveRecording(DeltaTime);
	}
	else if (Playing)
	{
		ResolvePlay();
	}
}

void URecordingStation::ResolveRecording(float DeltaTime)
{
	AccumulatedRecordingTimeSeconds += DeltaTime;
	SnapshotCount++;

	for (const TScriptInterface<IRecordable>& Recordable : Recordables)
	{
		Recordable->RecordSnapshot();
	}
}

void URecordingStation::ResolvePlay()
{
	for (const TScriptInterface<IRecordable>& Recordable : Recordables)
	{
		Recordable->PlaySnapshot(PlaySnapshotCount);
	}

	PlaySnapshotCount++;

	if (PlaySnapshotCount >= SnapshotCount)
	{
		StopPlaying();
	}
}

FString URecordingStation::GetFormattedAccumulatedTime() const
{
    int32 Minutes = FMath::FloorToInt(AccumulatedRecordingTimeSeconds / SECONDS_PER_MINUTE_FLOAT);
    int32 Seconds = FMath::FloorToInt(AccumulatedRecordingTimeSeconds) % SECONDS_PER_MINUTE;
    int32 Milliseconds = FMath::FloorToInt((AccumulatedRecordingTimeSeconds - FMath::FloorToInt(AccumulatedRecordingTimeSeconds)) * MILLISECONDS_PER_SECOND);
	return FString::Printf(TEXT("%02d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

void URecordingStation::AddRecordables(const TArray<TScriptInterface<IRecordable>>& RecordableArray)
{
	Recordables.Append(RecordableArray);
}

void URecordingStation::Interact(UItemHandle* ItemHandle)
{
	SwitchState();
}

void URecordingStation::SwitchState()
{
	if (Playing)
	{
		StopPlaying();
	}
	else if (Recording)
	{
		StartPlaying();
	}
	else
	{
		StartRecording();
	}

	OnInteract.Broadcast(Recording);
}

void URecordingStation::StartRecording()
{
	Recording = true;
	AccumulatedRecordingTimeSeconds = RESET_TIME;
	SnapshotCount = RESET_SNAPSHOT_COUNT;

	for (const TScriptInterface<IRecordable>& Recordable : Recordables)
	{
		Recordable->StartRecording();
	}
}

void URecordingStation::StartPlaying()
{
	Recording = false;
	Playing = true;
	PlaySnapshotCount = RESET_SNAPSHOT_COUNT;

	for (const TScriptInterface<IRecordable>& Recordable : Recordables)
	{
		Recordable->StartPlaying();
	}
}

void URecordingStation::StopPlaying()
{
	Playing = false;
	
	for (const TScriptInterface<IRecordable>& Recordable : Recordables)
	{
		Recordable->StopPlaying();
	}
}

bool URecordingStation::Interactable(UItemHandle* ItemHandle)
{
	return true;
}

FString URecordingStation::GetInteractionText()
{
	return Playing ? STOP_INTERACTION_TEXT : Recording ? PLAY_INTERACTION_TEXT : RECORD_INTERACTION_TEXT;
}

bool URecordingStation::GetIsRecording() const
{
	return Recording;
}

