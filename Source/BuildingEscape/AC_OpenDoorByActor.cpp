// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_OpenDoorByActor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"

// Called when the game starts
void UAC_OpenDoorByActor::BeginPlay()
{
	Super::BeginPlay();

	if (!ActorThatOpens)
	{
		ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}
