// Fill out your copyright notice in the Description page of Project Settings.

#include "Dimensions.h"
#include "Animation/AnimNodeBase.h"
#include "TimeReversableAnimInstance.h"


//This function is like PostInitAnimtree in UE3
void UTimeReversableAnimInstance::NativeInitializeAnimation()
{
	//Very Important Line
	Super::NativeInitializeAnimation();

	//Cache the owning pawn for use in Tick
	//OwningPawn = TryGetPawnOwner();

	UE_LOG(LogTemp, Warning, TEXT("Anim init, OWNER: %s"), *GetOwningComponent()->GetName());

}

//Tick
void UTimeReversableAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	USkeletalMeshComponent* skeletalComponent = GetOwningComponent();
	if (GetOwningComponent()->AnimationData.AnimToPlay) {
		UE_LOG(LogTemp, Warning, TEXT("ANIMATION PLAYING %s"), *GetOwningComponent()->AnimationData.AnimToPlay->GetName());
	}

	if (GetOwningComponent()->GetAnimInstance()->GetCurrentActiveMontage()) {
		UE_LOG(LogTemp, Warning, TEXT("HAS MONTAGE 1"));
	}

	if (GetOwningComponent()->GetSingleNodeInstance()) {
		UE_LOG(LogTemp, Warning, TEXT("HAS SINGLE NODE INSTANCE"));
	}
}

bool UTimeReversableAnimInstance::NativeEvaluateAnimation(FPoseContext& Output)
{
	/*if (Output.Pose.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>NativeEvaluateAnimation %d - %s"), Output.Pose.GetNumBones(), lastOutput == &Output ? TEXT("IDENTICAL"):TEXT("DIFF"));

		//if (lastOutput != &Output && lastOutput) {
			Output.ResetToRefPose();
		//}

		lastOutput = &Output;
	}*/

	return Super::NativeEvaluateAnimation(Output);
}