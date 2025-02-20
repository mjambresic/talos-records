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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemPlace);

	const FString DROP_INTERACTION_TEXT = "Drop";
	const FString PLACE_INTERACTION_TEXT = "Place";
	const FName PLACING_ENABLED_TAG = "CanHoldItem";
	const float NO_OFFSET = 0.0f;
	const int VERTICAL_TRACE_COUNT_TO_STEPS_MINUEND = 1;
	
	UItem* CurrentItem;
	UItemPad* CurrentItemPad;
	UCameraComponent* Camera;
	FString ItemInteractionText;
	bool CanPlaceItem;

	UPROPERTY(BlueprintAssignable)
	FOnItemPlace OnItemPlace;

	UPROPERTY(EditAnywhere)
	FVector ItemRotationOffset = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere)
	float PlacingDistance = 400;

	UPROPERTY(EditAnywhere)
	float VerticalTraceCount = 15;

	UPROPERTY(EditAnywhere)
	bool DebugEnabled = false;

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
	void ResolveItemPlacing();
	bool TryLineTrace(FHitResult& HitResult, AActor*& HitActor, UWorld* World, FVector StartPoint, FVector EndPoint, bool& HitSomething);
	bool TryHitEligibleItemHolderWithTrace(FHitResult& HitResult, AActor*& HitActor);
	bool TryHitEligibleItemHolderWithVerticalTraces(FHitResult& HitResult, AActor*& HitActor, UWorld* World, const FVector& MainTraceStartPoint, const FVector&
	                                                MainTraceEndPoint, bool& MainTraceHitSomething);
	bool TryResolveItemPlacingOnPad(const AActor* Actor);
	void ResolveItemPlacingOnNonPadSurface(const FHitResult& HitResult);
	void UpdatePlacementVisualizer(bool Visible, const FVector& Location, const FRotator& Rotation) const;
};