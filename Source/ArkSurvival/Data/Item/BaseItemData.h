#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseItemData.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum EItemCategory
{
	None        = 0 UMETA(DisplayName = "없음"),
	Weapon      = 1 << 0 UMETA(DisplayName = "무기"),
	Armor       = 1 << 1 UMETA(DisplayName = "장비"),
	Tool        = 1 << 2 UMETA(DisplayName = "도구"),
	Resource    = 1 << 3 UMETA(DisplayName = "자원"),
	Consumable  = 1 << 4 UMETA(DisplayName = "소비")
};

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FBaseItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "이름"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "아이콘"))
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EItemCategory", DisplayName = "카테고리"))
	int32 ItemCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "최대 스택 수"))
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "무게"))
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "설명"))
	FText Description;

	FBaseItemData()
	{
		ItemName = TEXT("");
		Icon = nullptr;
		ItemCategory = 0;
		MaxStackSize = 0;
		Weight = 0.f;
		Description = FText::GetEmpty();
	}
};
