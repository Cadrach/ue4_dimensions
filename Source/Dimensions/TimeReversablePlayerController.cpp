// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "TimeReversablePlayerController.h"


// Called when the game starts
void ATimeReversablePlayerController::BeginPlayingState()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TimeConto Started"));

	bShouldPerformFullTickWhenPaused = true;
}

