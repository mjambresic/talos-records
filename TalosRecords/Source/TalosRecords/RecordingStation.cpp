#include "RecordingStation.h"

const FString RECORD_INTERACTION_TEXT = TEXT("Record");
const FString PLAY_INTERACTION_TEXT = TEXT("Play");
const FString STOP_INTERACTION_TEXT = TEXT("Stop");
constexpr float RESET_TIME = 0.0f;
constexpr float SecondsPerMinuteFloat = 60.0f;
constexpr int32 SecondsPerMinute = 60; 
constexpr int32 MillisecondsPerSecond = 1000;

URecordingStation::URecordingStation()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = TickInterval;
}

void URecordingStation::BeginPlay()
{
	Super::BeginPlay();
}

// Remember that this component has custom Tick Interval set, to limit snapshotting performance impact.
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
		ResolvePlay(DeltaTime);
	}
}

void URecordingStation::ResolveRecording(float DeltaTime)
{
	AccumulatedRecordingTimeSeconds += DeltaTime;
}

void URecordingStation::ResolvePlay(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("Play."));
}

FString URecordingStation::GetFormattedAccumulatedTime() const
{
    int32 Minutes = FMath::FloorToInt(AccumulatedRecordingTimeSeconds / SecondsPerMinuteFloat);
    int32 Seconds = FMath::FloorToInt(AccumulatedRecordingTimeSeconds) % SecondsPerMinute;
    int32 Milliseconds = FMath::FloorToInt((AccumulatedRecordingTimeSeconds - FMath::FloorToInt(AccumulatedRecordingTimeSeconds)) * MillisecondsPerSecond);
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
}

void URecordingStation::StartPlaying()
{
	Recording = false;
	Playing = true;
}

void URecordingStation::StopPlaying()
{
	Playing = false;
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

