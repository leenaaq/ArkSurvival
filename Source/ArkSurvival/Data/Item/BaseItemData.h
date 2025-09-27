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
struct ARKSURVIVAL_API FBaseItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "이름"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "카테고리"))
	EItemCategory ItemCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "최대 스택 수"))
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "무게"))
	float Weight;

	FBaseItemData()
	{
		ItemName = TEXT("");
		ItemCategory = EItemCategory::None;
		MaxStackSize = 0;
		Weight = 0.f;
	}
};
