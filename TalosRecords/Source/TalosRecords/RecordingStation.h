#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "IRecordable.h"
#include "Components/ActorComponent.h"
#include "RecordingStation.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API URecordingStation : public UActorComponent, public IInteractable
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, bool, bRecording);

	const FString RECORD_INTERACTION_TEXT = "Record";
	const FString PLAY_INTERACTION_TEXT = "Play";
	const FString STOP_INTERACTION_TEXT = "Stop";
	const float RESET_TIME = 0.0f;
	const float SECONDS_PER_MINUTE_FLOAT = 60.0f;
	const int32 SECONDS_PER_MINUTE = 60; 
	const int32 MILLISECONDS_PER_SECOND = 1000;
	const int32 RESET_SNAPSHOT_COUNT = 0;

	bool Playing = false;
	bool Recording = false;
	float AccumulatedRecordingTimeSeconds = 0;
	int32 SnapshotCount = 0;
	int32 PlaySnapshotCount = 0;
	TArray<TScriptInterface<IRecordable>> Recordables;
	
	UPROPERTY(EditAnywhere)
	float MaxRecordingTimeSeconds = 300;

public:	
	URecordingStation();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;

	UFUNCTION(BlueprintCallable)
	bool GetIsRecording() const;

	UFUNCTION(BlueprintCallable)
	FString GetFormattedAccumulatedTime() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

	UFUNCTION(BlueprintCallable)
	void AddRecordables(const TArray<TScriptInterface<IRecordable>>& RecordableArray);

protected:
	virtual void BeginPlay() override;

private:
	void ResolveStates(float DeltaTime);
	void ResolveRecording(float DeltaTime);
	void ResolvePlay();
	void StopPlaying();
	void SwitchState();
	void StartRecording();
	void StartPlaying();
};
