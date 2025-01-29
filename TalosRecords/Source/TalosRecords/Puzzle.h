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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleEntered);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleExited);
	
	TArray<TScriptInterface<IObjective>> Objectives;
	UPuzzleGate* Gate;
	bool Entered = false;

public:	
	UPuzzle();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

protected:
	virtual void BeginPlay() override;

private:
	void ResolveObjectives();
};
