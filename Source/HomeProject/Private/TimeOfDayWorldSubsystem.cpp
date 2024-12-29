// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeOfDayWorldSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogTimeOfDay);

UTimeOfDayWorldSubsystem::UTimeOfDayWorldSubsystem()
{
}

void UTimeOfDayWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!IsValid(GetWorld()))
	{
		return;
	}

	UE_LOG(LogTimeOfDay, Warning, TEXT("Initialize"), TimeOfDay);
}

void UTimeOfDayWorldSubsystem::Deinitialize()
{
	UE_LOG(LogTimeOfDay, Warning, TEXT("Deinitialize"), TimeOfDay);
	Super::Deinitialize();
}

void UTimeOfDayWorldSubsystem::Tick(float DeltaTime)
{
	if (!IsValid(GetWorld()))
	{
		return;
	}

	TimeSinceLastTick += DeltaTime;
	if (TimeSinceLastTick < TickInterval)
	{
		return;
	}

	SetTimeOfDay(TimeOfDay + TimeScale * TimeSinceLastTick);
	TimeSinceLastTick = 0.0f;
}

void UTimeOfDayWorldSubsystem::SetTimeOfDay(float NewTimeOfDay)
{
	if (!IsValid(GetWorld()))
	{
		return;
	}

	TimeOfDay = FMath::Fmod(NewTimeOfDay, 24.0f);

	bool NewIsDayTime = TimeOfDay >= DawnTime && TimeOfDay < DuskTime;
	if (NewIsDayTime != bIsDayTime)
	{
		bIsDayTime = NewIsDayTime;
		bIsNightTime = !bIsDayTime;
		OnDayNightChanged.Broadcast(bIsNightTime);
	}

	OnTimeOfDayChanged.Broadcast(TimeOfDay, bIsNightTime);
}

FString UTimeOfDayWorldSubsystem::GetTimeOfDayAsString() const
{
	if (!IsValid(GetWorld()))
	{
		return FString();
	}

	int32 Hours = FMath::FloorToInt(TimeOfDay);
	int32 Minutes = FMath::RoundToInt((TimeOfDay - Hours) * 60.0f);
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Hours, Minutes);
	return TimeString;
}
