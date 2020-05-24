// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AC_OpenDoorTimeout.h"
#include "AC_OpenDoorByActor.h"
#include "CoreMinimal.h"
#include "AC_OpenDoorTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UAC_OpenDoorTrigger : public UAC_OpenDoorByActor, public UAC_OpenDoorTimeout
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
