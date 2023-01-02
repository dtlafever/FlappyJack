// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeSpawner.h"

// Sets default values
APipeSpawner::APipeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 2.0f;
	SpawnRateOffset = 0.5f;
	CurrentSpawnRate = 0.f;
	HeightOffset = 100.0f;
	Timer = 0.f;

}

void APipeSpawner::SpawnPipe()
{
	if (PipeActorClass)
	{
		float const RandomZOffset = FMath::FRandRange(HeightOffset * -1, HeightOffset);
		FVector const CurrentActorLocation = GetActorLocation();
		FVector const SpawnLocation = FVector(CurrentActorLocation.X, CurrentActorLocation.Y, CurrentActorLocation.Z + RandomZOffset);
		FRotator const SpawnRotation = GetActorRotation();
		GetWorld()->SpawnActor(PipeActorClass, &SpawnLocation, &SpawnRotation);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("APipeSpawner::spawnPipe Cannot spawn pipe. Missing Assigned Object to PipeActorClass."));
	}
	
}

void APipeSpawner::SetCurrentSpawnRate()
{
	float const RandomOffset = FMath::FRandRange(SpawnRateOffset * -1, SpawnRateOffset);
	CurrentSpawnRate = RandomOffset + SpawnRate;
}

// Called when the game starts or when spawned
void APipeSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPipe();
	SetCurrentSpawnRate();
}

// Called every frame
void APipeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timer < CurrentSpawnRate)
	{
		Timer += DeltaTime;
	}else
	{
		SpawnPipe();
		SetCurrentSpawnRate();
		Timer = 0;
	}
}

