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
}

void URecordingStation::Interact(UItemHandle* ItemHandle)
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
		Recording = true;
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

