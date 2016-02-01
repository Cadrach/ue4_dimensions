// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeReversableStateStruct.generated.h"

USTRUCT()
struct FTimeReversableStateStruct
{
	GENERATED_USTRUCT_BODY()


	//Constructors
	FTimeReversableStateStruct(){}
	FTimeReversableStateStruct(FVector l, FRotator r, FVector v, float t = 0) : location(l), rotation(r), velocity(v), time(t){}

	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated

	// So to simplify your life for later debugging, always use UPROPERTY()
	UPROPERTY()
	float time;

	UPROPERTY()
	FVector location;

	UPROPERTY()
	FRotator rotation;

	UPROPERTY()
	FVector velocity;

	//Get Time
	float GetTime() const
	{
		return time;
	}

	//Get Location
	FVector GetLocation() {
		return location;
	}

	//Get Rotation
	FRotator GetRotation() {
		return rotation;
	}

	//Get Velocity
	FVector GetVelocity() {
		return velocity;
	}

	//Set Time
	void SetTime(float newTime) {
		time = newTime;
	}
};  //Always remember this ;  at the end! You will get odd compile errors otherwise