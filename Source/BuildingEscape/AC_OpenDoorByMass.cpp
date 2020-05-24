// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoorByMass.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Called every frame
void UAC_OpenDoorByMass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (HasMassAccumulated())
    {
        OpenDoor();
        Timeout = GetWorld()->GetTimeSeconds() + WaitDelay;
    }
    else if (Timeout < GetWorld()->GetTimeSeconds())
    {
        CloseDoor();
    }
}

bool UAC_OpenDoorByMass::HasMassAccumulated() const
{

    float Mass = 0.f;

    TArray<AActor*> OverlappingActors;
    Trigger->GetOverlappingActors(OUT OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        auto Component = Actor->FindComponentByClass<UPrimitiveComponent>();
        if (Component->IsSimulatingPhysics())
        {
            Mass += Component->GetMass();
        }
    }

    return Mass >= MassToOpen;

}