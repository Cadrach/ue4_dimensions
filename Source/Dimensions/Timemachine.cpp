// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "TimeReversableComponent.h"
#include "Timemachine.h"

//General Log
DEFINE_LOG_CATEGORY(TimemachineLog);

// Sets default values
ATimemachine::ATimemachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimemachine::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Timemachine Started");
	UE_LOG(TimemachineLog, Warning, TEXT("Timemachine Started"));
	
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

}

// Called every frame
void ATimemachine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (auto Itr(observedActors.CreateIterator()); Itr; Itr++)
	{
		if (!(*Itr)->IsValidLowLevel()) continue;
		//~~~~~~~~~~~~~~~~~~~~~~

		//UE_LOG(LogTemp, Warning, TEXT("Actor %s is at %s"), *(*Itr)->GetName(), *(*Itr)->GetActorLocation().ToString());
	}
}

