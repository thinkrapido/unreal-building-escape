// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AC_OpenDoor.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "AC_OpenDoorByActor.generated.h"

UCLASS()
class BUILDINGESCAPE_API UAC_OpenDoorByActor : public UAC_OpenDoor
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	AActor *ActorThatOpens = nullptr;
};
