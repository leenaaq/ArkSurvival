#pragma once

#include "CoreMinimal.h"
#include "BaseItemData.h"
#include "Engine/DataTable.h"
#include "ConsumeItemData.generated.h"

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FConsumeItemData : public FBaseItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "체력"))
	float HealthValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "허기"))
	float FoodValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "수분"))
	float WaterValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "부패시간"))
	float SpoilTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "소비시간"))
	float ConsumptionTime = 0.0f;
};
