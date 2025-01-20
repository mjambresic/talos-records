#include "ObjectiveGate.h"

UObjectiveGate::UObjectiveGate()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObjectiveGate::BeginPlay()
{
	Super::BeginPlay();
}

void UObjectiveGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

