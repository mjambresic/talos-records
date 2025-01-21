#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetPlacementVisualizerLocation(FVector Location) const;

	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizerVisible(bool Visible) const;

	UFUNCTION(BlueprintCallable)
	void SetPlacementVisualizer(USceneComponent* Visualizer);

private:
	USceneComponent* PlacementVisualizer;
};
