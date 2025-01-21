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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float InteractionDistance = 400;

	UPROPERTY(EditAnywhere)
	float InteractionRadius = 100;
};
