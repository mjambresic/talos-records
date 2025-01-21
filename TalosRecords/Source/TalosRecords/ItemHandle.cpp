#include "ItemHandle.h"
#include "Camera/CameraComponent.h"

UItemHandle::UItemHandle()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemHandle::BeginPlay()
{
	Super::BeginPlay();
}

void UItemHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleItemTransform();
}

void UItemHandle::HandleItemTransform() const
{
	if (CurrentItemActor != nullptr)
	{
		CurrentItemActor->SetActorLocation(GetComponentLocation());

		UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
		Camera->GetComponentRotation();

		FRotator ItemRotation = FRotator
		(
			Camera->GetComponentRotation().Pitch + ItemRotationOffset.X,
			Camera->GetComponentRotation().Yaw + ItemRotationOffset.Z,
			Camera->GetComponentRotation().Roll + ItemRotationOffset.Y
		);
		
		CurrentItemActor->SetActorRotation(ItemRotation);
	}
}

bool UItemHandle::HandlesItem() const
{
	return CurrentItemActor != nullptr;
}

void UItemHandle::HandleItem(AActor* ActorToHandle)
{
	UPrimitiveComponent* InteractableActorPrimitiveComponent = ActorToHandle->FindComponentByClass<UPrimitiveComponent>();
	InteractableActorPrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentItemActor = ActorToHandle;
}

void UItemHandle::ReleaseItem()
{
	if (HandlesItem())
	{
		UPrimitiveComponent* InteractableActorPrimitiveComponent = CurrentItemActor->FindComponentByClass<UPrimitiveComponent>();
		InteractableActorPrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CurrentItemActor = nullptr;
	}
}


