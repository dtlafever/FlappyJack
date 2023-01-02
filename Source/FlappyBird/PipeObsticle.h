// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FlappyBirdGameMode.h"
#include "PipeObsticle.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeObsticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeObsticle();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* TopPipeMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* BottomPipeMesh;

	/* The GameMode we will use to call IncrementScore() */
	UPROPERTY(BlueprintReadOnly)
	AFlappyBirdGameMode * GameMode;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** called when something exits the BoxCollision to increase score */
    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
