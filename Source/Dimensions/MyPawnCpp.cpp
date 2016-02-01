// Fill out your copyright notice in the Description page of Project Settings.

#define LOCTEXT_NAMESPACE "GlobalText"
#include "Dimensions.h"
#include "Engine.h"
#include "MyPawnCpp.h"


// Sets default values
AMyPawnCpp::AMyPawnCpp()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;

}

// Called when the game starts or when spawned
void AMyPawnCpp::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AMyPawnCpp::AdvanceTimer, 1.0f, true);
}

// Called every frame
void AMyPawnCpp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyPawnCpp::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("MYPAWN PLAYERINPUT"));
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMyPawnCpp::UpdateTimerDisplay()
{
	CountdownText->SetText(FText::AsNumber(FMath::Max(CountdownTime, 0)));
}

void AMyPawnCpp::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		//We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void AMyPawnCpp::CountdownHasFinished()
{
	//Change to a special readout
	CountdownText->SetText(LOCTEXT("GO!", "GO!"));
}