// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UAC_OpenDoor::UAC_OpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UAC_OpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AnimateDoor(DeltaTime);
}

// Called when the game starts
void UAC_OpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!Trigger)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no preassure plate set"), *GetOwner()->GetName());
	}

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	ResetDoor();

	FindAudioComponent();
}

void UAC_OpenDoor::FindAudioComponent()
{
	Audio = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!Audio)
	{
		UE_LOG(LogTemp, Warning, TEXT("No audio component avialable for %s."), *GetOwner()->GetName());
	}
}

void UAC_OpenDoor::ResetDoor()
{
	FRotator OpenDoor{0.f, InitialYaw, 0.f};
	State = DoorState::Closed;
}
void UAC_OpenDoor::CloseDoor()
{
	switch (State)
	{
	case DoorState::Closed:
	case DoorState::Closing:
		return;
	}


	TargetYaw = InitialYaw;
	State = DoorState::Closing;
}
void UAC_OpenDoor::OpenDoor()
{
	switch (State)
	{
	case DoorState::Open:
	case DoorState::Opening:
		return;
	}

	TargetYaw = InitialYaw + TargetAngle * (OpenInward ? 1.0f : -1.0f);
	State = DoorState::Opening;

	if (Audio && !Audio->IsPlaying())
	{
		Audio->Play();
	}
}
void UAC_OpenDoor::AnimateDoor(float DeltaTime)
{
	switch (State)
	{
	case DoorState::Opening:
	case DoorState::Closing:
		float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

		FRotator OpenDoor{0.f, FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, SpeedFactor), 0.f};

		GetOwner()->SetActorRotation(OpenDoor);

		//UE_LOG(LogTemp, Warning, TEXT("open %f, %f %s."), CurrentYaw, TargetYaw, *GetOwner()->GetName());
		if (FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 3.f))
		{
			switch (State)
			{
			case DoorState::Closing:
				State = DoorState::Closed;

				if (Audio && !Audio->IsPlaying())
				{
					Audio->Play();
				}
				break;
			case DoorState::Opening:
				State = DoorState::Open;
				break;
			default:
				break;
			}
		}
		break;
	}
}