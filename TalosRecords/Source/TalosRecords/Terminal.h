#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "Components/ActorComponent.h"
#include "Terminal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UTerminal : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	UTerminal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;
};
