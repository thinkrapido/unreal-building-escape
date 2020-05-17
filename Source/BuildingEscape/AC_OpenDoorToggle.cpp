// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoorToggle.h"

// Called every frame
void UAC_OpenDoorToggle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Trigger && Trigger->IsOverlappingActor(ActorThatOpens))
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

        if (!HasJustEntered)
        {
            switch (State)
            {
            case DoorState::Open:
                CloseDoor();
                break;
            case DoorState::Closed:
                OpenDoor();
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
