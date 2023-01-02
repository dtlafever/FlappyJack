// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlappyBird.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, FlappyBird, "FlappyBird" );

double NormalizeToRange(double Value, double RangeMin, double RangeMax)
{
	if (RangeMin == RangeMax)
	{
		if (Value < RangeMin)
		{
			return 0.f;
		}
		else
		{
			return 1.f;
		}
	}

	if (RangeMin > RangeMax)
	{
		Swap(RangeMin, RangeMax);
	}
	return (Value - RangeMin) / (RangeMax - RangeMin);
}