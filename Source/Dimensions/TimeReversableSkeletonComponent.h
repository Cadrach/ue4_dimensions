// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeReversableComponent.h"
#include "TimeReversableSkeletonComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIMENSIONS_API UTimeReversableSkeletonComponent : public UTimeReversableComponent
{
	GENERATED_BODY()

public:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReverseToTime(float time) override;

	//The skeleton component
	USkeletalMeshComponent* skeletalComponent;
	
	FAnimNode_StateMachine* GetStateMachineInstance(int32 MachineIndex);
};