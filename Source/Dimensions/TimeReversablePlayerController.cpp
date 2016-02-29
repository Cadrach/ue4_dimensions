// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "Timemachine.h"
#include "TimeReversableComponent.h"
#include "TimeReversablePlayerController.h"


// Called when the game starts
void ATimeReversablePlayerController::BeginPlayingState()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TimeConto Started"));

	bShouldPerformFullTickWhenPaused = true;

	InputComponent->BindAction("TimeMachine", IE_Pressed, this, &ATimeReversablePlayerController::ReverseTimeStart);
	InputComponent->BindAction("TimeMachine", IE_Released, this, &ATimeReversablePlayerController::ReverseTimeStop).bExecuteWhenPaused = true;
	
	pawnTimeReversableComponent = Cast<UTimeReversableComponent>(GetPawn()->GetComponentByClass(UTimeReversableComponent::StaticClass()));
	if ( ! pawnTimeReversableComponent) {
		UE_LOG(TimemachineLog, Fatal, TEXT("ATimeReversablePlayerController => UTimeReversableComponent NOT PRESENT!!!"));
	}
}

void ATimeReversablePlayerController::ReverseTimeStart()
{
	UE_LOG(TimemachineLog, Error, TEXT("=========> PC REVERSING"));
	ClientIgnoreLookInput(true);
}

void ATimeReversablePlayerController::ReverseTimeStop()
{
	UE_LOG(TimemachineLog, Error, TEXT("=========> PC REVERSING STOP"));
	ClientIgnoreLookInput(false);
}

void ATimeReversablePlayerController::UpdateRotation(float DeltaSeconds) {
	Super::UpdateRotation(DeltaSeconds);
	if (IsPaused()) {
		//UE_LOG(TimemachineLog, Error, TEXT("PC => ROTATOR %s"), *(newComponent->latestRotation).ToString());
		ClientSetRotation(pawnTimeReversableComponent->latestRotation, false);

	}
}