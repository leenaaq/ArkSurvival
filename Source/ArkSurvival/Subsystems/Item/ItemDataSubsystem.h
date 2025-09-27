#pragma once

#include "CoreMinimal.h"
#include "ArkSurvival/Data/Item/ConsumeItemData.h"
#include "ArkSurvival/Data/Item/EquipmentItemData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "ItemDataSubsystem.generated.h"

UCLASS()
class ARKSURVIVAL_API UItemDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// 소비템 DataTable
	UPROPERTY()
	UDataTable* ConsumableDataTable;

	// 장비 DataTable
	UPROPERTY()
	UDataTable* EquipmentDataTable;

	// 소비템 맵
	UPROPERTY()
	TMap<int32, FConsumeItemData> ConsumableDataMap;

	// 장비 맵
	UPROPERTY()
	TMap<int32, FEquipmentItemData> EquipmentDataMap;

	void LoadAllItemTables();

	FConsumeItemData GetConsumableData(int32 ItemID) const;
	FEquipmentItemData GetEquipmentData(int32 ItemID) const;

	bool IsValidConsumableID(int32 ItemID) const;
	bool IsValidEquipmentID(int32 ItemID) const;
};
