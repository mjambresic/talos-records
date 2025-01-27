#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "Components/ActorComponent.h"
#include "RecordingStation.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API URecordingStation : public UActorComponent, public IInteractable
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, bool, bRecording);

public:	
	URecordingStation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual FString GetInteractionText() override;

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

private:
	FString InteractionText = "Record";
	bool Recording = false;
	bool Playing = false;
};
