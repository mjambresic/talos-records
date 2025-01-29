#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "IRecordable.h"
#include "ItemSnapshot.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItem : public UActorComponent, public IInteractable, public IRecordable
{
	GENERATED_BODY()

	USceneComponent* PlacementVisualizer;
	USceneComponent* RecordingVisualizer;
	UShapeComponent* Collider;
	FItemSnapshot PreRecordingSnapshot;
	TArray<FItemSnapshot> Snapshots;
	
	UPROPERTY(EditAnywhere)
	FString InteractionText = "Take Item";

	UPROPERTY(EditAnywhere)
	float BaseOffset = 0.0f;

	UPROPERTY(EditAnywhere)
	float Radius = 60.0f;

public:	
	UItem();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetPlacementVisualizerLocation(FVector Location) const;
	void SetPlacementVisualizerRotation(const FRotator& Rotation) const;
	void SetItemTransformToVisualizerTransform() const;
	void SetCollisionEnabled(ECollisionEnabled::Type CollisionType) const;
	void SetInteractionCollisionResponse(ECollisionResponse Response) const;
	float GetItemRadius() const;
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;
	virtual void StartRecording() override;
	virtual void RecordSnapshot() override;
	virtual void PlaySnapshot(int32 Index) override;
	virtual void StartPlaying() override;
	virtual void StopPlaying() override;
	
	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizerVisible(bool Visible) const;

	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizer(USceneComponent* Visualizer);

	UFUNCTION(BlueprintCallable)
	void SetRecordingVisualizerVisible(bool Visible) const;
	
	UFUNCTION(BlueprintCallable)
	void SetRecordingVisualizer(USceneComponent* Visualizer);

	UFUNCTION(BlueprintCallable)
	void SetCollider(UShapeComponent* ShapeCollider);

protected:
	virtual void BeginPlay() override;

private:
	void ResetToPreRecordingState() const;
};
