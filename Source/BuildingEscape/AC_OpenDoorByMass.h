// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AC_OpenDoorTimeout.h"
#include "AC_OpenDoor.h"
#include "CoreMinimal.h"
#include "AC_OpenDoorByMass.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UAC_OpenDoorByMass : public UAC_OpenDoor, public UAC_OpenDoorTimeout
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (ClampMin = "0.0"))
	float MassToOpen = 100.0f;

private:

	bool HasMassAccumulated() const;
};
