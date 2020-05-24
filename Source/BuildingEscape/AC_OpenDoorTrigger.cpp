// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoorTrigger.h"
#include "Engine/World.h"

// Called every frame
void UAC_OpenDoorTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Trigger && Trigger->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
        Timeout = GetWorld()->GetTimeSeconds() + WaitDelay;
    }
    else if (Timeout < GetWorld()->GetTimeSeconds())
    {
        CloseDoor();
    }
}
