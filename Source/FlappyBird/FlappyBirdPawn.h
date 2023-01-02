// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FlappyBirdGameMode.h"
// #include "Sound/SoundCue.h"
#include "Audio.h"
#include "FlappyBirdPawn.generated.h"

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPawn : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AFlappyBirdPawn();

protected:

	/** Sphere collision used to determine if we hit a pipe or passed between two pipes */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	USphereComponent* SphereCollision;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* BirdMesh;

	/* used for applying gravity to bird */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UProjectileMovementComponent * ProjectileMovement;

	/* The amount the bird will jump up when the player "flaps". */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float FlapStrength;

	/* Whether the bird is alive, determining if input should be accepted and game over. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAlive;

	/* The min rotation we tilt the bird based on its velocity */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TiltMin;

	/* The max rotation we tilt the bird based on its velocity */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TiltMax;

	/* The GameMode we will use to call GameOver() */
	UPROPERTY(BlueprintReadOnly)
	AFlappyBirdGameMode * GameMode;

	UPROPERTY(EditDefaultsOnly, Category="AssignValues")
	TSubclassOf<UCameraShakeBase> CameraShakeObj;

	UPROPERTY(EditDefaultsOnly, Category="AssignValues")
	USoundBase* HitSound;
	
	/* The tags to check if we are colliding with a pipe */
	FName PipeTag = FName("Pipe");
	FName PipeMeshTag = FName("PipeMesh");
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the this actor is being destroyed
	virtual void Destroyed() override;
	
	/** called when something enters the SphereCollision */
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/* tilts the bird based on the velocity. Used for visual effect. */
	UFUNCTION()
	void TiltBird();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Changes velocity of bird based on FlapStrength. */
	UFUNCTION(BlueprintCallable)
	void Flap();

	UFUNCTION(BlueprintCallable)
	bool GetIsAlive();

};
