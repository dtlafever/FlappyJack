// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FlappyBirdSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UFlappyBirdSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SaveGame")
	int32 PlayerHighScore = 0;

	UFUNCTION(BlueprintCallable)
	void SetValues(int32 NewScore)
	{
		PlayerHighScore = NewScore;
	}
	
	void Serialize(FArchive& Ar) override
	{
		Super::Serialize(Ar);

		Ar << PlayerHighScore;
	}
};
