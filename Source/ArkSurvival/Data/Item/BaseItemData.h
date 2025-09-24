#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseItemData.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	None        UMETA(DisplayName = "None"),
	Weapon      UMETA(DisplayName = "Weapon"),
	Armor       UMETA(DisplayName = "Armor"),
	Tool        UMETA(DisplayName = "Tool"),
	Resource    UMETA(DisplayName = "Resource"),
	Consumable  UMETA(DisplayName = "Consumable")
};

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FBaseItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemCategory ItemCategory = EItemCategory::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString IconPath = TEXT("");
    
	FBaseItemData()
	{
		ItemID = 0;
		ItemName = TEXT("");
		ItemCategory = EItemCategory::None;
		IconPath = TEXT("");
	}
};
