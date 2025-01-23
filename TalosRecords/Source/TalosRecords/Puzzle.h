#pragma once

#include "CoreMinimal.h"
#include "IObjective.h"
#include "PuzzleGate.h"
#include "Components/ActorComponent.h"
#include "Puzzle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UPuzzle : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPuzzle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ResolveObjectives();
	
	UFUNCTION(BlueprintCallable)
	void SetPuzzleGate(UPuzzleGate* Gate);
	
	UFUNCTION(BlueprintCallable)
	void AddObjectives(const TArray<TScriptInterface<IObjective>>& ObjectiveArray);


private:
	TArray<TScriptInterface<IObjective>> Objectives;
	UPuzzleGate* PuzzleGate;
};
