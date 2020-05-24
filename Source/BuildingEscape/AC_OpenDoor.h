// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "AC_OpenDoor.generated.h"

enum DoorState
{
	Open,
	Closed,
	Opening,
	Closing,
};

UCLASS()
class BUILDINGESCAPE_API UAC_OpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_OpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	const float DOOR_OPEN_ANGLE = 120.f;

	float TargetYaw = 0.f;
	float InitialYaw = 0.f;
	DoorState State = DoorState::Closed;


	UPROPERTY(EditAnywhere, Meta = (CampMin = "0.001", ClampMax = "100.0"))
	float SpeedFactor = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float TargetAngle = 90.f;

	UPROPERTY(EditAnywhere)
	bool OpenInward = true;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *Trigger = nullptr;

	UAudioComponent *Audio = nullptr;
	void FindAudioComponent();

	void ResetDoor();
	void CloseDoor();
	void OpenDoor();
	void AnimateDoor(float DeltaTime);
};
