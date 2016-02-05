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

	UE_LOG(LogTemp, Warning, TEXT("Anim init"));
}

//Tick
void UTimeReversableAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	/*UE_LOG(LogTemp, Warning, TEXT("Anim update %s position: %f active: %s"), 
		*(Montage_GetCurrentSection(GetCurrentActiveMontage())).ToString(),
		Montage_GetPosition(GetCurrentActiveMontage()),
		Montage_IsActive(GetCurrentActiveMontage()) ? TEXT("TRUE"): TEXT("FALSE")
		);*/
}

bool UTimeReversableAnimInstance::NativeEvaluateAnimation(FPoseContext& Output)
{
	if (Output.Pose.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>NativeEvaluateAnimation %d"), Output.Pose.GetNumBones());
	}

	return Super::NativeEvaluateAnimation(Output);
}