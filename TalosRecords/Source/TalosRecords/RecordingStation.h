#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "Components/ActorComponent.h"
#include "RecordingStation.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API URecordingStation : public UActorComponent, public IInteractable
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, bool, bRecording);

public:	
	URecordingStation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ResolveStates(float DeltaTime);
	void ResolveRecording(float DeltaTime);
	void ResolvePlay(float DeltaTime);
	void StopPlaying();
	void SwitchState();
	void StartRecording();
	void StartPlaying();
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;

	UFUNCTION(BlueprintCallable)
	bool GetIsRecording() const;

	UFUNCTION(BlueprintCallable)
	FString GetFormattedAccumulatedTime() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

private:
	FString InteractionText = "Record";
	bool Playing = false;
	bool Recording = false;
	float AccumulatedRecordingTimeSeconds = 0;
	
	UPROPERTY(EditAnywhere)
	float MaxRecordingTimeSeconds = 300;
};
