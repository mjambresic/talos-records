#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interaction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UInteraction : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	UInteraction();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void OnInteractActionPressed() const;
	
private:
	void DrawDebug(const FVector& StartPoint, const FVector& EndPoint) const;
	void ScanForInteractableObject(const FVector& StartPoint, const FVector& EndPoint);

protected:
	virtual void BeginPlay() override;

private:

	AActor* InteractableActor;
	
	UPROPERTY(EditAnywhere)
	float InteractionDistance = 400;

	UPROPERTY(EditAnywhere)
	float InteractionRadius = 100;

	UPROPERTY(EditAnywhere)
	float DebugEnabled = true;
};
