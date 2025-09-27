#pragma once

#include "CoreMinimal.h"
#include "BaseItemData.h"
#include "Engine/DataTable.h"
#include "EquipmentItemData.generated.h"

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FEquipmentItemData : public FBaseItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "내구도"))
	int32 Durability = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "방어력"))
	int32 ArmorValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "장착부위"))
	FString EquipSlot = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "추위저항"))
	int32 ColdResist = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "더위저항"))
	int32 HeatResist = 0;
};
