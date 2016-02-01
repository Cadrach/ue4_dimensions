// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "TimeReversableComponent.h"
#include "TimeMachine.generated.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(TimemachineLog, Log, All);

UCLASS()
class DIMENSIONS_API ATimeMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeMachine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Start Reversing Time
	void ReverseTimeStart();

	//Stop Reversing Time
	void ReverseTimeStop();

	//Array of observed Actors
	UPROPERTY(EditAnywhere)
	TArray<AActor*> observedActors;

	//Are we reversing time?
	bool bReversingTime;
};
