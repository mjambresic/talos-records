#pragma once

#include "CoreMinimal.h"
#include "IRecordable.h"
#include "PlayerCharacterSnapshot.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALOSRECORDS_API UPlayerCharacter : public UActorComponent, public IRecordable
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAnimationValueUpdate, FVector, Velocity, float, GroundSpeed, bool, ShouldMove, bool, IsFalling);
	const float GROUND_SPEED_THRESHOLD = 3.0f;

	USceneComponent* ThirdPersonPlayerMesh;
	UCharacterMovementComponent* MovementComponent;
	TArray<FPlayerCharacterSnapshot> Snapshots;

public:	
	UPlayerCharacter();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void StartRecording() override {};
	virtual void RecordSnapshot() override;
	virtual void PlaySnapshot(int32 Index) override;
	virtual void StartPlaying() override;
	virtual void StopPlaying() override;

	UFUNCTION(BlueprintCallable)
	void SetMovementComponent(UCharacterMovementComponent* Component);

	UFUNCTION(BlueprintCallable)
	void SetThirdPersonRecordingVisualizer(USceneComponent* Component);

	UPROPERTY(BlueprintAssignable)
	FOnAnimationValueUpdate OnPlaySnapshotAnimationValues;

protected:
	virtual void BeginPlay() override;
};