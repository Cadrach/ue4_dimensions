// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TimeReversableStateStruct.h"
#include "TimeReversableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIMENSIONS_API UTimeReversableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeReversableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Return to a previous state in time
	void ReverseToTime(float time);

	//Offset all pastStates by time
	void OffsetTimeBy(float time);

	//Array of observed Actors
	FVector latestLocation;
	
	//
	TArray<FTimeReversableStateStruct> pastStates;
};
