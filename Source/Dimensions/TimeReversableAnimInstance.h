// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "Animation/AnimNodeBase.h"
#include "TimeReversableAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DIMENSIONS_API UTimeReversableAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	
	virtual bool NativeEvaluateAnimation(FPoseContext& Output) override;
};
