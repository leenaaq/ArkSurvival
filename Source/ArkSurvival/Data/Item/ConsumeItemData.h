#pragma once

#include "CoreMinimal.h"
#include "BaseItemData.h"
#include "Engine/DataTable.h"
#include "ConsumeItemData.generated.h"

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FConsumeItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseItemData BaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FoodValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpoilTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ConsumptionTime = 0.0f;
};