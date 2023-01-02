// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeObsticle.h"
#include "GameFramework/GameMode.h"
#include "FlappyBirdPawn.h"

// Sets default values
APipeObsticle::APipeObsticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	moveSpeed = 5;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	TopPipeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopPipeMesh"));
	TopPipeMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TopPipeMesh->ComponentTags.Add(FName("PipeMesh"));

	BottomPipeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomPipeMesh"));
	BottomPipeMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BottomPipeMesh->ComponentTags.Add(FName("PipeMesh"));

	Tags.Add(FName("Pipe"));
}

// Called when the game starts or when spawned
void APipeObsticle::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &APipeObsticle::OnOverlapEnd);

	GameMode = Cast<AFlappyBirdGameMode, AGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("APipeObsticle::BeginPlay Cannot cast GameModeBase -> AFlappyBirdGameMode."))
	}
	
}

void APipeObsticle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherComp)
	{
		AFlappyBirdPawn* FlappyBird = Cast<AFlappyBirdPawn, AActor>(OtherActor);
		if (FlappyBird) // confirm OtherActor is a FlappyBirdPawn
		{
			if (GameMode && FlappyBird->GetIsAlive())
			{
				GameMode->IncrementScore();
			}
		}
	}
}

// Called every frame
void APipeObsticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FTransform newTransform = GetActorTransform();
	// Multiplying by delta time so it is independent of framerate.
	newTransform.SetLocation(newTransform.GetLocation() + FVector(0, -moveSpeed,0) * DeltaTime);
	SetActorTransform(newTransform);
	
}

