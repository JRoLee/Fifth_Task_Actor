// Fill out your copyright notice in the Description page of Project Settings.


#include "EssentialActor.h"

// Sets default values
AEssentialActor::AEssentialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AEssentialActor::Move()
{
	//Set random location num
	double Start = -4000.0f;
	double End = 4000.0f;

	double RandNum1 = FMath::RandRange(Start, End);
	double RandNum2 = FMath::RandRange(Start, End);
	double RandNum3 = FMath::RandRange(Start, End);

	//Move random location
	FVector NewLocation = FVector(RandNum1, RandNum2, RandNum3);
	SetActorLocation(NewLocation);

	//Print moved location
	FVector ActorLocation = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue,
			FString::Printf(TEXT("Actor Location: %s"), *ActorLocation.ToString()));
	}
}

void AEssentialActor::Turn()
{
	//Set random rotation num
	double Start = 0.0f;
	double End = 360.0f;

	double RandNum1 = FMath::RandRange(Start, End);
	double RandNum2 = FMath::RandRange(Start, End);
	double RandNum3 = FMath::RandRange(Start, End);

	//Rotate random Rotation
	FRotator NewRotation = FRotator(RandNum1, RandNum2, RandNum3);
	SetActorRotation(NewRotation);
}

// Called when the game starts or when spawned
void AEssentialActor::BeginPlay()
{
	Super::BeginPlay();

	//Set start location and print location
	FVector StartLocation = FVector(0.0f, 50.0f, 0.0f);
	SetActorLocation(StartLocation);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue,
			FString::Printf(TEXT("Actor Start Location: %s"), *StartLocation.ToString()));
	}

	//10 times move and rotate
	for (int i = 0; i < 10; i++)
	{
		Move();
		Turn();
	}
	
}

// Called every frame
void AEssentialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

