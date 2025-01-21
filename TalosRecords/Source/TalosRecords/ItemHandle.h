#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
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
	void HandleItem(AActor* ActorToHandle);
	void HandleItemTransform() const;
	void HandleItemRotation() const;
	bool HandlesItem() const;
	void SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const;

	UFUNCTION(BlueprintCallable)
	void ReleaseItem();

private:
	AActor* CurrentItemActor;
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere)
	FVector ItemRotationOffset = FVector(0, 0, 0);
};