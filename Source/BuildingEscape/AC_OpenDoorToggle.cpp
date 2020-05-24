// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoorToggle.h"

// Called every frame
void UAC_OpenDoorToggle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Trigger && Trigger->IsOverlappingActor(ActorThatOpens))
    {
        if (!HasJustEntered)
        {
            switch (State)
            {
            case DoorState::Open:
                CloseDoor();
		UE_LOG(LogTemp, Warning, TEXT("close %s."), *GetOwner()->GetName());
                break;
            case DoorState::Closed:
                OpenDoor();
		UE_LOG(LogTemp, Warning, TEXT("open %s."), *GetOwner()->GetName());
                break;
            }
            HasJustEntered = true;
        }
    }
    else
    {
        HasJustEntered = false;
    }
}
