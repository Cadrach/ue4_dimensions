// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TimeReversablePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIMENSIONS_API ATimeReversablePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlayingState() override;

};
