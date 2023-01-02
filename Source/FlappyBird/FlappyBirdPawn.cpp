// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyBirdPawn.h"
#include "Kismet/GameplayStatics.h" // For playing camera shake and play sound
#include "FlappyBird.h"
#include "GameFramework/GameMode.h"

// Sets default values
AFlappyBirdPawn::AFlappyBirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlapStrength = 500.0f;
	IsAlive = true;
	TiltMin = -50.f;
	TiltMax = -10.f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	SphereCollision->SetSphereRadius(32.0f);

	BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->AttachToComponent(SphereCollision, FAttachmentTransformRules::KeepRelativeTransform);
	BirdMesh->SetSimulatePhysics(false);
	BirdMesh->SetGenerateOverlapEvents(false);
	BirdMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0f, 0.0f, 0.0f));
	ProjectileMovement->UpdateComponentVelocity();
}

// Called when the game starts or when spawned
void AFlappyBirdPawn::BeginPlay()
{
	Super::BeginPlay();

	// Bind Dynamic Delegate to handle when something overlaps with the bird
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AFlappyBirdPawn::OnOverlapBegin);
	
	GameMode = Cast<AFlappyBirdGameMode, AGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("AFlappyBirdPawn::BeginPlay Cannot cast GameModeBase -> AFlappyBirdGameMode."))
	}
	
}

void AFlappyBirdPawn::Destroyed()
{
	Super::Destroyed();

	if (GameMode)
	{
		GameMode->GameOver();
	}
}

void AFlappyBirdPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		if (IsAlive && OtherActor->ActorHasTag(PipeTag) && OtherComp->ComponentHasTag(PipeMeshTag))
		{
			IsAlive = false;
			if (GameMode)
			{
				GameMode->GameOver();
			}
			if (CameraShakeObj)
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeObj, GetActorLocation(), 0.0f, 10000.0f);
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySound2D(this, HitSound, 1.0f, 1.0f);
			}
		}
	}
}

void AFlappyBirdPawn::TiltBird()
{
	float NormalizedVelocity = NormalizeToRange(ProjectileMovement->Velocity.Z, FlapStrength * -1, FlapStrength);
	float NewRotationValue = FMath::Lerp(-50.f, -10.f, NormalizedVelocity);
	
	FRotator CurrentRotator = SphereCollision->GetComponentRotation();
	FRotator TiltRotator = FRotator(NewRotationValue,CurrentRotator.Yaw, CurrentRotator.Roll);
	SphereCollision->SetWorldRotation(TiltRotator);
}

// Called every frame
void AFlappyBirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TiltBird();
	
}

// Called to bind functionality to input
void AFlappyBirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFlappyBirdPawn::Flap()
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0f, 0.0f, FlapStrength));
	ProjectileMovement->UpdateComponentVelocity();
}

bool AFlappyBirdPawn::GetIsAlive()
{
	return IsAlive;
}
