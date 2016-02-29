// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TimeReversableComponent.h"
#include "TimeReversablePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIMENSIONS_API ATimeReversablePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlayingState() override;

	virtual void UpdateRotation(float DeltaSeconds) override;

	//Start Reversing Time
	void ReverseTimeStart();

	//Stop Reversing Time
	void ReverseTimeStop();

	//The component managing time reversal on the pawn
	UTimeReversableComponent *pawnTimeReversableComponent;

};
