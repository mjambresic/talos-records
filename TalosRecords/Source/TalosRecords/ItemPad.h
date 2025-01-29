#pragma once

#include "CoreMinimal.h"
#include "IObjective.h"
#include "Item.h"
#include "ItemPadSnapshot.h"
#include "Components/ActorComponent.h"
#include "ItemPad.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItemPad : public UActorComponent, public IInteractable, public IObjective, public IRecordable
{
	GENERATED_BODY()

	TArray<FItemPadSnapshot> Snapshots;
	FItemPadSnapshot PreRecordingSnapshot;
	USceneComponent* ItemSocket;
	UItem* CurrentItem;
	bool OverrideObjectiveCompleted = false;
	bool ActivatedByPlayer = false;

public:	
	UItemPad();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool CanPlaceItem() const;
	FVector GetSocketLocation() const;
	FRotator GetSocketRotation() const;
	void PlaceItem(UItem* Item);
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;	
	virtual void StartRecording() override;
	virtual void RecordSnapshot() override;
	virtual void PlaySnapshot(int32 Index) override;
	virtual void StartPlaying() override;
	virtual void StopPlaying() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetObjectiveCompleted() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetActivatedByPlayer(bool Activated);

	UFUNCTION(BlueprintCallable)
	void SetItemSocket(USceneComponent* ItemSocketSceneComponent);

protected:
	virtual void BeginPlay() override;

private:
	void ResetToPreRecordingState();
	bool HoldsItem() const;
};
