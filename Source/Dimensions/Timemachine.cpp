// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "TimeReversableComponent.h"
#include "Timemachine.h"

//General Log
DEFINE_LOG_CATEGORY(TimemachineLog);

// Sets default values
ATimeMachine::ATimeMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReversingTime = false;
	fTimeReversedCumulation = 0;
}

// Called when the game starts or when spawned
void ATimeMachine::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Timemachine Started");
	UE_LOG(TimemachineLog, Warning, TEXT("Timemachine Started"));

	//Get Player Controller
	PController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	//Listen to Input & Enable it
	PController->InputComponent->BindAction("TimeMachine", IE_Pressed, this, &ATimeMachine::ReverseTimeStart);
	PController->InputComponent->BindAction("TimeMachine", IE_Released, this, &ATimeMachine::ReverseTimeStop).bExecuteWhenPaused = true;
	EnableInput(PController);

	//Ticks execute when pausing the game, to allow charging the reversing
	SetTickableWhenPaused(true);

	//For each actor, check if correctly setup
	for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
	{
		if (!(*Itr)->IsValidLowLevel()) continue;
		UTimeReversableComponent *newComponent = Cast<UTimeReversableComponent>((*Itr)->GetComponentByClass(UTimeReversableComponent::StaticClass()));
		if (!newComponent) {
			UE_LOG(TimemachineLog, Fatal, TEXT("UTimeReversableComponent NOT PRESENT FOR %s"), *(*Itr)->GetName());
		}
		newComponent = NULL;
	}

}

void ATimeMachine::ReverseTimeStart()
{
	UE_LOG(TimemachineLog, Error, TEXT("********************************************"));
	UE_LOG(TimemachineLog, Error, TEXT("********************************************"));
	//Store time we start reversing
	fTimeReversingStartAt = GetWorld()->GetRealTimeSeconds();
	fTimeCharged = 0;
	//Pause Game
	PController->SetPause(true);
	//Start reversing time
	bReversingTime = true;
}

void ATimeMachine::ReverseTimeStop()
{
	//Stop Pause
	PController->SetPause(false);
	//Stop reversing time
	bReversingTime = false;
	//Increment cumulation
	fTimeReversedCumulation += fTimeCharged;

	UE_LOG(TimemachineLog, Error, TEXT("TIME REAL START %f"), fTimeReversingStartAt);
	UE_LOG(TimemachineLog, Error, TEXT("TIME REAL CURRENT %f"), GetWorld()->GetRealTimeSeconds());
	UE_LOG(TimemachineLog, Error, TEXT("TIME PLAY CURRENT %f"), GetWorld()->GetTimeSeconds());
	UE_LOG(TimemachineLog, Warning, TEXT("TIME CHARGED %f"), fTimeCharged);

	for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
	{
		//Get Component & Reverse it to time
		(Cast<UTimeReversableComponent>((*Itr)->GetComponentByClass(UTimeReversableComponent::StaticClass())))
			->OffsetTimeBy(fTimeCharged);
	}
}

// Called every frame
void ATimeMachine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bReversingTime) {
		fTimeCharged = GetWorld()->GetRealTimeSeconds() - fTimeReversingStartAt;
		//UE_LOG(LogTemp, Warning, TEXT("CHARGED %f"), fTimeCharged);

		for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
		{
			//Get Component & Reverse it to time
			(Cast<UTimeReversableComponent>((*Itr)->GetComponentByClass(UTimeReversableComponent::StaticClass())))
				->ReverseToTime(GetWorld()->GetTimeSeconds() - fTimeCharged);
		}
	}
}

