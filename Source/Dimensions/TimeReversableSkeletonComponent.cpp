// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

#include "Dimensions.h"
#include "Animation/AnimNode_StateMachine.h"
#include "TimeReversableSkeletonComponent.h"

// Called when the game starts
void UTimeReversableSkeletonComponent::BeginPlay()
{
	Super::BeginPlay();

	//Register Primitive component
	skeletalComponent = (Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass())));
	//skeletalComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent %s"), *skeletalComponent->GetName());
}

FAnimNode_StateMachine* UTimeReversableSkeletonComponent::GetStateMachineInstance(int32 MachineIndex)
{
	if (skeletalComponent->AnimBlueprintGeneratedClass)
	{
		if ((MachineIndex >= 0) && (MachineIndex < skeletalComponent->AnimBlueprintGeneratedClass->AnimNodeProperties.Num()))
		{
			const int32 InstancePropertyIndex = skeletalComponent->AnimBlueprintGeneratedClass->AnimNodeProperties.Num() - 1 - MachineIndex;

			UStructProperty* MachineInstanceProperty = skeletalComponent->AnimBlueprintGeneratedClass->AnimNodeProperties[InstancePropertyIndex];
			checkSlow(MachineInstanceProperty->Struct->IsChildOf(FAnimNode_StateMachine::StaticStruct()));

			return MachineInstanceProperty->ContainerPtrToValuePtr<FAnimNode_StateMachine>(skeletalComponent->GetAnimInstance());
		}
	}

	return nullptr;
}

// Called every frame
void UTimeReversableSkeletonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

/*	UE_LOG(LogTemp, Warning, TEXT("STATE %s %f"), 
		*skeletalComponent->GetAnimInstance()->GetCurrentStateName(0).ToString(),
		skeletalComponent->GetAnimInstance()->GetCurrentStateElapsedTime(0)
		);*/

	/*const int32 InstancePropertyIndex = skeletalComponent->AnimBlueprintGeneratedClass->AnimNodeProperties.Num() - 1;
	UStructProperty* MachineInstanceProperty = skeletalComponent->AnimBlueprintGeneratedClass->AnimNodeProperties[InstancePropertyIndex];
	checkSlow(MachineInstanceProperty->Struct->IsChildOf(FAnimNode_StateMachine::StaticStruct()));*/

	if (GetStateMachineInstance(0)) {
		//UE_LOG(LogTemp, Warning, TEXT("FOUND STATE MACHINE %s"), *GetStateMachineInstance(0)->GetCurrentStateName().ToString());
	}

	if (skeletalComponent->AnimationData.AnimToPlay) {
		UE_LOG(LogTemp, Warning, TEXT("ANIMATION PLAYING %s"), *skeletalComponent->AnimationData.AnimToPlay->GetName());
	}

	if (skeletalComponent->AnimScriptInstance && skeletalComponent->AnimScriptInstance->GetCurrentActiveMontage()) {
		UE_LOG(LogTemp, Warning, TEXT("HAS MONTAGE 1"));
	}

	UAnimMontage *montage = Cast<ACharacter>(GetOwner())->GetCurrentMontage();
	if (montage) {
		UE_LOG(LogTemp, Warning, TEXT("HAS MONTAGE 2"));
	}

	if (skeletalComponent->GetSingleNodeInstance()) {
		UE_LOG(LogTemp, Warning, TEXT("HAS SINGLE NODE INSTANCE"));
	}
	//skeletalComponent->GetSingleNodeInstance()->StopAnim();
	

	if (skeletalComponent->AnimScriptInstance && skeletalComponent->AnimScriptInstance->GetCurrentActiveMontage()) {
		for (int32 I = 0; I < skeletalComponent->AnimScriptInstance->GetCurrentActiveMontage()->SlotAnimTracks.Num(); ++I) {

			UE_LOG(LogTemp, Warning, TEXT("Slot name %s"),
				*skeletalComponent->AnimScriptInstance->GetCurrentActiveMontage()->SlotAnimTracks[I].SlotName.ToString()
				);
		}
	}
}

void UTimeReversableSkeletonComponent::ReverseToTime(float time) {
	Super::ReverseToTime(time);
	//skeletalComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
}