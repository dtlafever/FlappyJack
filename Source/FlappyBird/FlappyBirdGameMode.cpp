// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameMode.h"
#include "Kismet/GameplayStatics.h" // For pausing game
AFlappyBirdGameMode::AFlappyBirdGameMode()
{
	Score = 0;
	CurrentHighScore = 0;
	ReachedNewHighScore = false;
}

void AFlappyBirdGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Score != 0)
	{
		// Special effects for every 10 points
		if (Score % 10 == 0)
		{
			// make sure we only play this effect once per 10 points.
			if (AbleToPlay10PointEffects)
			{
				AbleToPlay10PointEffects = false;
				HandlePer10Points();
			}
		}else
		{
			// reset bool so we can use it again for the 10 points
			AbleToPlay10PointEffects = true;
		}
		
		// Handle new high score code
		if (!ReachedNewHighScore)
		{
			if (Score > CurrentHighScore)
			{
				ReachedNewHighScore = true;
				HandleNewHighScore();
			}
		}
	}
}

void AFlappyBirdGameMode::IncrementScore()
{
	Score++;
}

void AFlappyBirdGameMode::ResetScore()
{
	Score = 0;
}

int32 AFlappyBirdGameMode::GetScore()
{
	return Score;
}

void AFlappyBirdGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	SaveGameObj = Cast<UFlappyBirdSaveGame, USaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
	if (!SaveGameObj)
	{
		// No save game created, instantiate SaveGame object so we can save later.
		SaveGameObj = NewObject<UFlappyBirdSaveGame>();
	}
	else
	{
		// Loaded our save, lets load the current high score
		CurrentHighScore = SaveGameObj->PlayerHighScore;
	}
}

void AFlappyBirdGameMode::SaveGame()
{
	if (ReachedNewHighScore)
	{
		if (SaveGameObj)
		{
			CurrentHighScore = Score;
			SaveGameObj->SetValues(CurrentHighScore);
			bool SaveSuccesful = UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveName, 0);
			if (SaveSuccesful)
			{
				UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdGameMode::SaveGame Save Succesful!"))
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdGameMode::SaveGame Save Failed."))
			}
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdGameMode::SaveGame SaveGameObj not valid. Save Failed."));
		}
	}
}