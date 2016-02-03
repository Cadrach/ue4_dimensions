// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

#include "Dimensions.h"
#include "TimeReversableSkeletonComponent.h"

// Called when the game starts
void UTimeReversableSkeletonComponent::BeginPlay()
{
	Super::BeginPlay();

	//Register Primitive component
	skeletalComponent = (Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass())));

}


// Called every frame
void UTimeReversableSkeletonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (skeletalComponent->GetAnimInstance()->GetActiveMontageInstance()) {
		FAnimMontageInstance *montage = skeletalComponent->GetAnimInstance()->GetActiveMontageInstance();
		UE_LOG(LogTemp, Warning, TEXT("Time fraction %f"),
		//montage->GetCurrentSection(),
			skeletalComponent->GetAnimInstance()->GetActiveMontageInstance()->GetPosition()
		);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Skeleton name %s"), *skeletalComponent->GetName());
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance name %s"), *skeletalComponent->GetAnimInstance()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("Time fraction %f"), *(*skeletalComponent->GetAnimInstance()->GetActiveMontageInstance()->GetNextSection()));
	}

}
