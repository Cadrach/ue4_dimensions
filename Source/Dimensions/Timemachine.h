// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Timemachine.generated.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(TimemachineLog, Log, All);

UCLASS()
class DIMENSIONS_API ATimemachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimemachine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Array of observed Actors
	UPROPERTY(EditAnywhere)
	TArray<AActor*> observedActors;
	
};
