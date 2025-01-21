#pragma once

#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ItemHandle.h"
#include "Interaction.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class TALOSRECORDS_API UInteraction : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	UInteraction();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void OnPrimaryActionPressed() const;
	
private:
	void DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const;
	void ScanForInteractableObject(const FVector& StartPoint, const FVector& EndPoint);

protected:
	virtual void BeginPlay() override;

private:

	AActor* InteractableActor;
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
