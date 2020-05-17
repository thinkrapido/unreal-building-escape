// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AC_OpenDoor.h"
#include "CoreMinimal.h"
#include "AC_OpenDoorTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UAC_OpenDoorTrigger : public UAC_OpenDoor
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (ClampMin = "0.0"))
	float WaitDelay = 0.f;

private:
	float Timeout = 0.f;
};
