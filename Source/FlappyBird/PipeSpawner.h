// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeSpawner.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PipeActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRateOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeightOffset;

	float Timer;

	void SpawnPipe();

private:
	float CurrentSpawnRate;

	void SetCurrentSpawnRate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
