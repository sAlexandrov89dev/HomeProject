// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeOfDayWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HOMEPROJECT_API UTimeOfDayWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TickInterval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TimeOfDay = 12.0f;

	UPROPERTY(EditAnywhere, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TimeScale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float DawnTime = 6.0f;

	UPROPERTY(EditAnywhere, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float DuskTime = 18.0f;

	UPROPERTY(EditAnywhere, Category = "Time of Day")
	bool bIsDayTime = false;

	UPROPERTY(EditAnywhere, Category = "Time of Day")
	bool bIsNightTime = false;

	float TimeSinceLastTick = 0.0f;
};
