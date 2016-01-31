// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "TimeReversableComponent.h"


// Sets default values for this component's properties
UTimeReversableComponent::UTimeReversableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	UE_LOG(LogTemp, Warning, TEXT("Timecomponent CONSTRUCTOR"));

	// ...
}


// Called when the game starts
void UTimeReversableComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Timecomponent Started"));
	// ...
	
}


// Called every frame
void UTimeReversableComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//UE_LOG(LogTemp, Warning, TEXT("Timecomponent TICKING"));
	// ...
}

