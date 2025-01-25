#include "Terminal.h"

UTerminal::UTerminal()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTerminal::BeginPlay()
{
	Super::BeginPlay();
}

void UTerminal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTerminal::Interact(UItemHandle* ItemHandle)
{
	OnInteract.Broadcast();
}

bool UTerminal::Interactable(UItemHandle* ItemHandle)
{
	return true;
}

