#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItem : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	UItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetPlacementVisualizerLocation(FVector Location) const;
	void SetPlacementVisualizerRotation(const FRotator& Rotation) const;
	void SetItemTransformToVisualizerTransform() const;
	virtual void Interact(UItemHandle* ItemHandle) override;
	void SetCollisionEnabled(ECollisionEnabled::Type CollisionType) const;
	void SetInteractionCollisionResponse(ECollisionResponse Response) const;
	virtual bool Interactable(UItemHandle* ItemHandle) override;

	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizerVisible(bool Visible) const;

	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizer(USceneComponent* Visualizer);

	UFUNCTION(BlueprintCallable)
	void SetCollider(UShapeComponent* ShapeCollider);

private:
	USceneComponent* PlacementVisualizer;
	UShapeComponent* Collider;

	UPROPERTY(EditAnywhere)
	float BaseOffset = 0.0f;
};
