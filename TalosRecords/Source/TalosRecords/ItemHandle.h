#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Item.h"
#include "ItemPad.h"
#include "ItemHandle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItemHandle : public USceneComponent
{
	GENERATED_BODY()
	
	const FString DROP_INTERACTION_TEXT = "Drop";
	const FString PLACE_INTERACTION_TEXT = "Place";
	const FName PLACING_ENABLED_TAG = "CanHoldItem";
	
	UItem* CurrentItem;
	UItemPad* CurrentItemPad;
	UCameraComponent* Camera;
	FString ItemInteractionText;
	bool CanPlaceItem;

	UPROPERTY(EditAnywhere)
	FVector ItemRotationOffset = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere)
	float PlacingDistance = 400;

public:	
	UItemHandle();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TakeItem(UItem* Item);
	bool HasItem() const;
	
	UFUNCTION(BlueprintCallable)
	bool GetCanPlaceItem() const;

	UFUNCTION(BlueprintCallable)
	FString GetItemInteractionText() const;

	UFUNCTION(BlueprintCallable)
	void PlaceItemToEligiblePlace();

protected:
	virtual void BeginPlay() override;

private:
	void HandleItemTransform() const;
	void HandleItemRotation() const;
	void SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const;
	void PlaceItem();
	void ResolveItemPlacingTrace();
	bool ItemPlacingTrace(FHitResult& HitResult) const;
	bool TryCheckIfActorIsTaggedToHoldItem(const AActor* Actor);
	bool TryResolveVisualizationOnPad(const AActor* Actor);
	void ResolveItemPlacingOnNonPadSurface(const FHitResult& HitResult);
	void UpdatePlacementVisualizer(bool Visible, const FVector& Location, const FRotator& Rotation) const;
};