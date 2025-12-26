// Fill out your copyright notice in the Description page of Project Settings.


#include "ChallengeActor.h"

// Sets default values
AChallengeActor::AChallengeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AChallengeActor::Move(TArray<FVector>* Location)
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
	Location->Add(FVector(NewLocation));

	//Print moved location
	FVector ActorLocation = GetActorLocation();
}

void AChallengeActor::Turn()
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

void RandEvent(int Posibility, int* EventNum)
{
	int RandNum = FMath::RandRange(1, 100);
	if (RandNum > Posibility)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Orange,
				FString::Printf(TEXT("Event Triggered!")));
		}
		*EventNum += 1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Black,
			FString::Printf(TEXT("Event Not Triggered!")));
	}
}

float Distance(const FVector& first, const FVector& second)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	float dz = first.Z - second.Z;

	return FMath::Sqrt(dx * dx + dy * dy + dz * dz);
}

float TotalDistance(const TArray<FVector>& Array)
{
	float TotalDistance = 0;
	for (int i = 0; i < Array.Num()-1; i++)
	{
		TotalDistance += Distance(Array[i], Array[i + 1]);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red,
				FString::Printf(TEXT("TotalDistance: %f"),TotalDistance));
		}
	}
	return TotalDistance;
}


// Called when the game starts or when spawned
void AChallengeActor::BeginPlay()
{
	Super::BeginPlay();
	
	int EventNum = 0;
	TArray<FVector> LocationArray;

	//Set start location and print location
	FVector StartLocation = FVector(0.0f, 50.0f, 0.0f);
	SetActorLocation(StartLocation);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue,
			FString::Printf(TEXT("Actor Start Location: %s"), *StartLocation.ToString()));
	}
	LocationArray.Add(FVector(StartLocation));

	//10 times move and rotate
	for (int i = 0; i < 10; i++)
	{
		Move(&LocationArray);
		Turn();
		RandEvent(50, &EventNum);
	}

	float Distance = TotalDistance(LocationArray);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green,
			FString::Printf(TEXT("Event happend: %d times"),EventNum));

		GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green,
			FString::Printf(TEXT("Total moved distance: %f"), Distance));
	}

}

// Called every frame
void AChallengeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

