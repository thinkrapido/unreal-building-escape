// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Components/ActorComponent.h"
#include "ObjectMacros.h"

/**
 * 
 */
class UAC_OpenDoorTimeout
{

protected:
	UPROPERTY(EditAnywhere, Meta = (ClampMin = "0.0"))
	float WaitDelay = 0.f;

	float Timeout = 0.f;
};
