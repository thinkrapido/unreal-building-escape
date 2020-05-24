// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "AC_Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UAC_Grabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_Grabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0.0"))
	float Reach = 100.f;

private:
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;

	void FindPhysicsHandle();
	void FindInputComponent();

	void GrabComponent();
	void ReleaseComponent();

	std::pair<FVector, FRotator> GetPlayerLocationAndRotator() const;
	FVector GetGrabLocation() const;
	FHitResult GetHitResult() const;
};
