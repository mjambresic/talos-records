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

public:	
	UItemPad();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FVector GetSocketLocation() const;
	FRotator GetSocketRotation() const;
	bool CanPlaceItem() const;
	bool CanTakeItem() const;
	void PlaceItem(UItem* Item);
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;	
	virtual void StartRecording() override;
	virtual void RecordSnapshot() override;
	virtual void PlaySnapshot(int32 Index) override;
	virtual void StartPlaying() override;
	virtual void StopPlaying() override;
	void ResetToPreRecordingState();
	bool HasItemPlaced() const;

	UFUNCTION(BlueprintCallable)
	virtual bool IsCompleted() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetActivatedByPlayer(bool Activated);

	UFUNCTION(BlueprintCallable)
	void SetItemSocket(USceneComponent* ItemSocketSceneComponent);
	
private:
	TArray<FItemPadSnapshot> Snapshots;
	bool OverrideObjectiveCompleted = false;
	bool ActivatedByPlayer = false;
	FItemPadSnapshot PreRecordingSnapshot;
	USceneComponent* ItemSocket;
	UItem* CurrentItem;
};
