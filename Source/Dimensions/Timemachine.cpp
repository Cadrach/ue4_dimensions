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
	APlayerController *PCOwner = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	//Listen to Input
	PCOwner->InputComponent->BindAction("TimeMachine", IE_Pressed, this, &ATimeMachine::ReverseTimeStart);
	PCOwner->InputComponent->BindAction("TimeMachine", IE_Released, this, &ATimeMachine::ReverseTimeStop);
	EnableInput(PCOwner);

	//For each actor, check if correctly setup
	for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
	{
		if (!(*Itr)->IsValidLowLevel()) continue;
		//~~~~~~~~~~~~~~~~~~~~~~

		UTimeReversableComponent *newComponent = Cast<UTimeReversableComponent>((*Itr)->GetComponentByClass(UTimeReversableComponent::StaticClass()));

		if (!newComponent) {
			UE_LOG(TimemachineLog, Error, TEXT("NO COMPONENT PRESENT %s"), *(*Itr)->GetName());
		}

		/*UTimeReversableComponent *newComponent = NewObject<UTimeReversableComponent>(UTimeReversableComponent::StaticClass());
		(*Itr)->AddInstanceComponent(newComponent);
		newComponent->RegisterComponent();*/
		//newComponent->AttachParent = (*Itr);
		//newComponent->RegisterAllComponentTickFunctions(true);

		/*auto newComponent = (*Itr)->CreateComponentFromTemplate(UTimeReversableComponent::templ);
		newComponent->RegisterComponent();
		newActor->AddInstanceComponent(newComponent);*/

		//newComponent->InitializeComponent();



		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, (*Itr)->GetName());

		UE_LOG(LogTemp, Warning, TEXT("Actor %s is at %s"), *(*Itr)->GetName(), *(*Itr)->GetActorLocation().ToString());
		//UE_LOG(LogTemp, Warning, (*Itr)->GetActorLocation());

		newComponent = NULL;
	}

	PCOwner = NULL;

}

void ATimeMachine::ReverseTimeStart()
{
	bReversingTime = true;
}

void ATimeMachine::ReverseTimeStop()
{
	bReversingTime = false;
}

// Called every frame
void ATimeMachine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bReversingTime) {
		UE_LOG(LogTemp, Warning, TEXT("Reversing Time"));
	}

	for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
	{
		if (!(*Itr)->IsValidLowLevel()) continue;
		//~~~~~~~~~~~~~~~~~~~~~~

		//UE_LOG(LogTemp, Warning, TEXT("Actor %s is at %s"), *(*Itr)->GetName(), *(*Itr)->GetActorLocation().ToString());
	}
}

