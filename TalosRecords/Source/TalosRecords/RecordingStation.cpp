#include "RecordingStation.h"

URecordingStation::URecordingStation()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URecordingStation::BeginPlay()
{
	Super::BeginPlay();
}

void URecordingStation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResolveStates(DeltaTime);
}

void URecordingStation::ResolveStates(float DeltaTime)
{
	if (Recording)
	{
		Record(DeltaTime);
	}
	else if (Playing)
	{
		Play(DeltaTime);
	}
}

void URecordingStation::Record(float DeltaTime)
{
	AccumulatedRecordingTimeSeconds += DeltaTime;
}

void URecordingStation::Play(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("Play."));
}

void URecordingStation::Stop()
{
	UE_LOG(LogTemp, Display, TEXT("Stop playing."));
	Recording = false;
	Playing = false;
}

FString URecordingStation::GetFormattedAccumulatedTime() const
{
	int32 Minutes = FMath::FloorToInt(AccumulatedRecordingTimeSeconds / 60.0f);
	int32 Seconds = FMath::FloorToInt(AccumulatedRecordingTimeSeconds) % 60;
	int32 Milliseconds = FMath::FloorToInt((AccumulatedRecordingTimeSeconds - FMath::FloorToInt(AccumulatedRecordingTimeSeconds)) * 1000);
	return FString::Printf(TEXT("%02d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

void URecordingStation::Interact(UItemHandle* ItemHandle)
{
	SwitchState();
}

void URecordingStation::SwitchState()
{
	if (Playing)
	{
		Playing = false;
	}
	else if (Recording)
	{
		Recording = false;
		Playing = true;
	}
	else
	{
		// Starts Recording
		Recording = true;
		AccumulatedRecordingTimeSeconds = 0;
	}

	OnInteract.Broadcast(Recording);
}

bool URecordingStation::Interactable(UItemHandle* ItemHandle)
{
	return true;
}

FString URecordingStation::GetInteractionText()
{
	return Playing ? FString("Stop") : Recording ? FString("Play") : FString("Record");
}

bool URecordingStation::GetIsRecording() const
{
	return Recording;
}

