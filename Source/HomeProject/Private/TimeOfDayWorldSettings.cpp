// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeOfDayWorldSettings.h"

void ATimeOfDayWorldSettings::SetTimeOfDayDefaults(UWorld* World, float NewTimeOfDay)
{
	if (World == nullptr)
	{
		return;
	}

	if (ATimeOfDayWorldSettings* TimeOfDayWorldSettings = Cast<ATimeOfDayWorldSettings>(World->GetWorldSettings()))
	{
		TimeOfDayWorldSettings->DefaultTimeOfDay = NewTimeOfDay;
	}
}
