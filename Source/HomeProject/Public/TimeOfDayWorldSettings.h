// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "TimeOfDayWorldSettings.generated.h"

UCLASS()
class HOMEPROJECT_API ATimeOfDayWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "24.0"), Category = "Time Of Day")
	float DefaultTimeOfDay = 12.0f;	

	// Static function to set the time of day defaults from blueprints
	UFUNCTION(BlueprintCallable, Category = "Time Of Day")
	static void SetTimeOfDayDefaults(class UWorld* World, float NewTimeOfDay);
};
