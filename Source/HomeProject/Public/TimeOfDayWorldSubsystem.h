#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Delegates/DelegateCombinations.h"
#include "Delegates/Delegate.h"
#include "UObject/SparseDelegate.h"
#include "TimeOfDayWorldSubsystem.generated.h"

// Define custom logger
DECLARE_LOG_CATEGORY_EXTERN(LogTimeOfDay, Log, All);

// This delegate will broadcast a float whenever time-of-day changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTimeOfDayChangedDelegate, float, TimeOfDay, bool, bIsNightTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayNightChangedDelegate, bool, bIsNightTime);

UCLASS()
class HOMEPROJECT_API UTimeOfDayWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UTimeOfDayWorldSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}
	virtual bool IsTickableInEditor() const override
	{
		return false;
	}

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Time of Day")
	void SetTimeOfDay(float NewTimeOfDay);

	UFUNCTION(BlueprintCallable, Category = "Time of Day")
	FString GetTimeOfDayAsString() const;

	UPROPERTY(BlueprintAssignable, Category = "Time of Day")
	FTimeOfDayChangedDelegate OnTimeOfDayChanged;

	UPROPERTY(BlueprintAssignable, Category = "Time of Day")
	FDayNightChangedDelegate OnDayNightChanged;

protected:
	UPROPERTY(EditAnywhere, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TickInterval = 0.04f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TimeOfDay = 12.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float TimeScale = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float DawnTime = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float DuskTime = 18.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day")
	bool bIsDayTime = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time of Day")
	bool bIsNightTime = false;

private:
	float TimeSinceLastTick = 0.0f;
};