// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeReversableStateStruct.generated.h"

USTRUCT()
struct FTimeReversableStateStruct
{
	GENERATED_USTRUCT_BODY()


	//Constructors
	FTimeReversableStateStruct(){}
	FTimeReversableStateStruct(FVector l, FRotator r, float t = 0) : location(l), rotation(r), time(t){}

	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated

	// So to simplify your life for later debugging, always use UPROPERTY()
	UPROPERTY()
	float time;

	UPROPERTY()
	FVector location;

	UPROPERTY()
	FRotator rotation;

	//Set
	void SetFloat(float NewValue)
	{
		time = NewValue;
	}

	void SetLocation(FVector NewValue) {
		location = NewValue;
	}
};  //Always remember this ;  at the end! You will get odd compile errors otherwise