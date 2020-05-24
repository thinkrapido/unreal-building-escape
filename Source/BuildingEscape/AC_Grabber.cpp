// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UAC_Grabber::UAC_Grabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAC_Grabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	FindInputComponent();
}

// Called every frame
void UAC_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetGrabLocation());
	}
}

void UAC_Grabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s."), *GetOwner()->GetName());
	}
}
void UAC_Grabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UAC_Grabber::GrabComponent);
		InputComponent->BindAction("Grab", IE_Released, this, &UAC_Grabber::ReleaseComponent);
	}
}

void UAC_Grabber::GrabComponent()
{
	FHitResult HitResult = GetHitResult();

	if (HitResult.GetActor() && PhysicsHandle) {
		auto Component = HitResult.GetComponent();
		PhysicsHandle->GrabComponentAtLocation(
			Component,
			NAME_None,
			GetGrabLocation()
			);
	}
}
void UAC_Grabber::ReleaseComponent()
{
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

std::pair<FVector, FRotator> UAC_Grabber::GetPlayerLocationAndRotator() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Get players viewport
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	return std::pair<FVector, FRotator>(PlayerViewPointLocation, PlayerViewPointRotation);
}
FVector UAC_Grabber::GetGrabLocation() const
{
	auto [PlayerViewPointLocation, PlayerViewPointRotator] = GetPlayerLocationAndRotator();
	return PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
}

FHitResult UAC_Grabber::GetHitResult() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams{FName(TEXT("")), false, GetOwner()};

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerLocationAndRotator().first,
		GetGrabLocation(),
		FCollisionObjectQueryParams{ECollisionChannel::ECC_PhysicsBody},
		TraceParams
		);

	return Hit;
}
