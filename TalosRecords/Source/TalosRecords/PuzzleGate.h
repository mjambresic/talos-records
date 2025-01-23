#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleGate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UPuzzleGate : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPuzzleGate();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetOpen(bool Open);

private:
	void Open(float DeltaTime) const;
	void Close(float DeltaTime) const;
	void Move(float DeltaTime, const FVector& TargetLocation) const;
	void ResolveOpenStatus(float DeltaTime) const;

protected:
	virtual void BeginPlay() override;

private:

	FVector BeginLocation = FVector::ZeroVector;
	float MoveSpeed = 0.0f;
	
	UPROPERTY(EditAnywhere)
	FVector OpenOffset = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
	float OpenDuration = 1.0f;

	UPROPERTY(EditAnywhere)
	bool IsOpen = false;
};
