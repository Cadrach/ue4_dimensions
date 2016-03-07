// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "TimeReversableComponentPlayer.h"



// Called when the game starts
void UTimeReversableComponentPlayer::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> array = GetOwner()->GetComponents();

	//Register Primitive component
	for (int32 Index = array.Num() - 1; Index > 0; --Index)
	{
		UE_LOG(LogTemp, Error, TEXT("TimecomponentPlayer %s => %s [%s]"), 
			*GetOwner()->GetName(), 
			*array[Index]->GetName(),
			*array[Index]->GetClass()->GetFName().ToString()
			);
	}

}

// Called every frame
void UTimeReversableComponentPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	pastStates.Last().SetRotation(GetOwner()->GetActorRotation());
	// ...
}

