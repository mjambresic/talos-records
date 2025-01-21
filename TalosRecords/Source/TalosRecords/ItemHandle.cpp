#include "ItemHandle.h"

UItemHandle::UItemHandle()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemHandle::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
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
		HandleItemRotation();
	}
}

void UItemHandle::HandleItemRotation() const
{
	FRotator ItemRotation = FRotator
	(
		Camera->GetComponentRotation().Pitch + ItemRotationOffset.X,
		Camera->GetComponentRotation().Yaw + ItemRotationOffset.Z,
		Camera->GetComponentRotation().Roll + ItemRotationOffset.Y
	);
		
	CurrentItemActor->SetActorRotation(ItemRotation);
}

bool UItemHandle::HandlesItem() const
{
	return CurrentItemActor != nullptr;
}

void UItemHandle::HandleItem(AActor* ActorToHandle)
{
	CurrentItemActor = ActorToHandle;
	SetItemPhysicsProperties(ECollisionEnabled::NoCollision);
}

void UItemHandle::ReleaseItem()
{
	if (HandlesItem())
	{
		SetItemPhysicsProperties(ECollisionEnabled::QueryAndPhysics);
		CurrentItemActor = nullptr;
	}
}

void UItemHandle::SetItemPhysicsProperties(ECollisionEnabled::Type CollisionType) const
{
	UPrimitiveComponent* InteractableActorPrimitiveComponent = CurrentItemActor->FindComponentByClass<UPrimitiveComponent>();
	InteractableActorPrimitiveComponent->SetCollisionEnabled(CollisionType);
}
