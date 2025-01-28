#pragma once

#include "Components/SceneComponent.h"
#include "ItemHandle.h"
#include "Interaction.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TALOSRECORDS_API UInteraction : public USceneComponent
{
	GENERATED_BODY()
	const int32 ALLOWED_INTERACTABLE_COMPONENT_COUNT = 1;

public:	
	UInteraction();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void OnPrimaryActionPressed() const;

protected:
	virtual void BeginPlay() override;
	
private:
	void DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const;
	void ScanForInteractableObject(const FVector& StartPoint, const FVector& EndPoint);
	void ResolveInteractableObjectFromHitResult(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintCallable)
	FString GetInteractableObjectText() const;
	
	UFUNCTION(BlueprintCallable)
	bool HasValidInteractableObject() const;

	// PROPERTIES
	IInteractable* InteractableObject;
	UItemHandle* ItemHandle;
	
	UPROPERTY(EditAnywhere)
	float InteractionDistance = 200;
	
	UPROPERTY(EditAnywhere)
	float InteractionRadius = 50;
	
	UPROPERTY(EditAnywhere)
	float DebugEnabled = true;
	
	UPROPERTY(EditAnywhere)
	float ItemHoldDistance = 150;
};
