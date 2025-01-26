#pragma once

#include "CoreMinimal.h"
#include "IObjective.h"
#include "PuzzleGate.h"
#include "Components/ActorComponent.h"
#include "Puzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleEntered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleExited);

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
	void ResolveEnter();

	UFUNCTION(BlueprintCallable)
	void ResolveExit();
	
	UFUNCTION(BlueprintCallable)
	void SetPuzzleGate(UPuzzleGate* PuzzleGate);
		
	UFUNCTION(BlueprintCallable)
	void AddObjectives(const TArray<TScriptInterface<IObjective>>& ObjectiveArray);

	UPROPERTY(BlueprintAssignable)
	FPuzzleEntered PuzzleEntered;
	
	UPROPERTY(BlueprintAssignable)
	FPuzzleExited PuzzleExited;

private:
	TArray<TScriptInterface<IObjective>> Objectives;
	UPuzzleGate* Gate;
	bool Entered = false;
};
