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
	
	//Register Primitive component
	primitiveComponent = (Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass())));
	
}

// Called every frame
void UTimeReversableComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (GetOwner()->GetActorLocation().Equals(latestLocation) && GetOwner()->GetActorRotation().Equals(latestRotation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Timecomponent TICKING UNCHANGED LOCATION %s"), *(GetOwner()->GetName()));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Timecomponent TICKING NEW STATE %s, past states: %d"), *(GetOwner()->GetActorLocation()).ToString(), pastStates.Num());
		pastStates.Add(
			FTimeReversableStateStruct(
				GetOwner()->GetActorLocation(),
				GetOwner()->GetActorRotation(),
				primitiveComponent->GetPhysicsLinearVelocity(),
				primitiveComponent->GetPhysicsAngularVelocity(),
				GetWorld()->GetTimeSeconds()
				)
			);
	}
	latestLocation = GetOwner()->GetActorLocation();
	latestRotation = GetOwner()->GetActorRotation();

	// ...
}

void UTimeReversableComponent::ReverseToTime(float time)
{
	//Parse registered states in reverse
	for (int32 Index = pastStates.Num() - 1; Index > 0; --Index)
	{
		if (pastStates[Index].GetTime() > time)
		{
			pastStates.RemoveAt(Index, 1, true);
		}
		else {
			break;
		}
	}

	//Apply latest state
	GetOwner()->SetActorLocation(pastStates.Last().GetLocation());
	GetOwner()->SetActorRotation(pastStates.Last().GetRotation());
	primitiveComponent->SetPhysicsLinearVelocity(pastStates.Last().GetVelocityLinear());
	primitiveComponent->SetPhysicsAngularVelocity(pastStates.Last().GetVelocityAngular());
	latestLocation = GetOwner()->GetActorLocation();
	latestRotation = GetOwner()->GetActorRotation();
}

void UTimeReversableComponent::OffsetTimeBy(float time)
{
	UE_LOG(LogTemp, Warning, TEXT("FIRST STATE BEFORE %f"), pastStates[0].GetTime());

	//Parse registered states
	for (int32 Index = 0; Index < pastStates.Num(); Index++)
	{
		pastStates[Index].SetTime(pastStates[Index].GetTime() + time);
	}

	UE_LOG(LogTemp, Warning, TEXT("FIRST STATE AFTER %f"), pastStates[0].GetTime());
}