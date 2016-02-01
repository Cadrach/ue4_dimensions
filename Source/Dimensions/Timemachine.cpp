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
			UE_LOG(TimemachineLog, Error, TEXT("NO COMPONENT PRESENT %s"), *(*Itr)->GetName());
		}
		newComponent = NULL;
	}

}

void ATimeMachine::ReverseTimeStart()
{
	//Store time we start reversing
	reversingTimeStartAt = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	//Pause Game
	PController->SetPause(true);
	//Start reversing time
	bReversingTime = true;
}

void ATimeMachine::ReverseTimeStop()
{
	PController->SetPause(false);
	bReversingTime = false;
}

// Called every frame
void ATimeMachine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bReversingTime) {
		float chargedTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - reversingTimeStartAt;
		//UE_LOG(LogTemp, Warning, TEXT("Reversing Time %f"), chargedTime);

		for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
		{
			UTimeReversableComponent *TimeComponent = Cast<UTimeReversableComponent>((*Itr)->GetComponentByClass(UTimeReversableComponent::StaticClass()));
			FTimeReversableStateStruct TimeState = TimeComponent->ReverseToTime(reversingTimeStartAt - chargedTime);
			//UE_LOG(LogTemp, Warning, TEXT("Reversing Time %f"), chargedTime);
			(*Itr)->SetActorLocation(TimeState.GetLocation());
		}

		chargedTime = NULL;
	}
}

