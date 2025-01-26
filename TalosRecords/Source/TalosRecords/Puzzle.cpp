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
			Gate->SetOpen(false);
			return;
		}
	}

	Gate->SetOpen(true);
}

void UPuzzle::ResolveEnter()
{
	if (Entered)
	{
		return;
	}

	Entered = true;
	PuzzleEntered.Broadcast();
}

void UPuzzle::ResolveExit()
{
	if (!Entered)
	{
		return;
	}
	
	Entered = false;
	PuzzleExited.Broadcast();

	// TODO: Reset puzzle on exit.
}

void UPuzzle::SetPuzzleGate(UPuzzleGate* PuzzleGate)
{
	Gate = PuzzleGate;
}

void UPuzzle::AddObjectives(const TArray<TScriptInterface<IObjective>>& ObjectiveArray)
{
	Objectives.Append(ObjectiveArray);
}
