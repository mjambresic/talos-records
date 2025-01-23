#include "Puzzle.h"

UPuzzle::UPuzzle()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

void UPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResolveObjectives();
}

void UPuzzle::ResolveObjectives()
{
	for (const TScriptInterface<IObjective>& Objective : Objectives)
	{
		if (!Objective->IsCompleted())
		{
			PuzzleGate->SetOpen(false);
			return;
		}
	}

	PuzzleGate->SetOpen(true);
}

void UPuzzle::SetPuzzleGate(UPuzzleGate* Gate)
{
	PuzzleGate = Gate;
}

void UPuzzle::AddObjectives(const TArray<TScriptInterface<IObjective>>& ObjectiveArray)
{
	Objectives.Append(ObjectiveArray);
}
