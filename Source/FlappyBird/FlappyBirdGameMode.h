// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FlappyBirdSaveGame.h"
#include "Audio.h"
#include "FlappyBirdGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFlappyBirdGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void IncrementScore();

	UFUNCTION(BlueprintCallable)
	void ResetScore();

	UFUNCTION(BlueprintCallable)
	int32 GetScore();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GameOver();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartGame();

	/* sound that is played when you reach 10 successful passthroughs */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AssignValues")
	USoundBase* PassSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Function to call when we beat the current high score */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HandleNewHighScore();

	/* play any sounds and HUD effects every 10 points */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HandlePer10Points();

	/* save new high score to a .sav file */
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UFlappyBirdSaveGame* SaveGameObj;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SaveName = "SaveGame";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentHighScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ReachedNewHighScore;
	
private:
	int32 Score = 0;

	/* Our gate to prevent more than 1 trigger per 10 points */
	bool AbleToPlay10PointEffects = true;
	
};
