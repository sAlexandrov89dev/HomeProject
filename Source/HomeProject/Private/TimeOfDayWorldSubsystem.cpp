// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeOfDayWorldSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
		

void UTimeOfDayWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Time of Day Initialize !!!"));

	const UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time of Day Initialize No World"));
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("Is Tickable: %s"), IsTickable() ? TEXT("True") : TEXT("False"));

	UE_LOG(LogTemp, Warning, TEXT("Time of Day Initialize World: %s"), *World->GetName());

	const EWorldType::Type WorldType = World->WorldType;
	if (WorldType == EWorldType::Editor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time of Day Initialize Editor"), TimeOfDay);
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Time of Day Initialize!!!"), TimeOfDay);
	//UE_LOG(LogTemp, Warning, TEXT("World Type: %s"), *UEnum::GetValueAsString(WorldType));
}

void UTimeOfDayWorldSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Time of Day Deinitialize"), TimeOfDay);
}

void UTimeOfDayWorldSubsystem::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Time of Day Tick global"), TimeOfDay);
	
	TimeSinceLastTick += DeltaTime;
	if (TimeSinceLastTick < TickInterval)
	{
		return;
	}

	if (GIsEditor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Time of Day Tick Editor"), TimeOfDay);
		//return;
	}
	
	TimeOfDay += DeltaTime * TimeScale;
	TimeOfDay = FMath::Fmod(TimeOfDay, 24.0f);

	bIsDayTime = TimeOfDay >= DawnTime && TimeOfDay < DuskTime;
	bIsNightTime = !bIsDayTime;

	//UE_LOG(LogTemp, Warning, TEXT("Time of Day: %f"), TimeOfDay);
	//UE_LOG(LogTemp, Warning, TEXT("Is Day Time: %s"), bIsDayTime ? TEXT("True") : TEXT("False"));

	TimeSinceLastTick = 0.0f;

}
