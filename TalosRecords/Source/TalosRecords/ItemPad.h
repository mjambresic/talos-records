#pragma once

#include "CoreMinimal.h"
#include "IObjective.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "ItemPad.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UItemPad : public UActorComponent, public IInteractable, public IObjective
{
	GENERATED_BODY()

public:	
	UItemPad();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FVector GetSocketLocation() const;
	FRotator GetSocketRotation() const;
	bool CanPlaceItem() const;
	bool CanTakeItem() const;
	void PlaceItem(UItem* Item);
	UItem* TakeItem();
	virtual void Interact(UItemHandle* ItemHandle) override;
	virtual bool Interactable(UItemHandle* ItemHandle) override;
	virtual bool IsCompleted() override;
	
	UFUNCTION(BlueprintCallable)
	void SetItemSocket(USceneComponent* ItemSocketSceneComponent);
	
private:
	USceneComponent* ItemSocket;
	UItem* CurrentItem;
};
