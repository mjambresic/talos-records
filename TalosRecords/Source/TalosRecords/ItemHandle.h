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

public:	
	UItemHandle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void PickUpItem(UItem* Item);
	void HandleItemTransform() const;
	void HandleItemRotation() const;
	bool HasItem() const;
	void SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const;
	void PlaceItem();
	void ResolveItemPlacingTrace();
	bool TryCheckIfActorIsTaggedToHoldItem(const AActor* Actor);
	bool TryResolveVisualizationOnPad(const AActor* Actor);
	void UpdatePlacementVisualizer(bool Visible, const FVector& Location, const FRotator& Rotation) const;

	UFUNCTION(BlueprintCallable)
	void PlaceItemToEligiblePlace();

private:
	UItem* CurrentItem;
	UItemPad* CurrentItemPad;
	UCameraComponent* Camera;
	bool HitActorCanHoldItem;
	
	UPROPERTY(EditAnywhere)
	FVector ItemRotationOffset = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
	float PlacingDistance = 400;
};