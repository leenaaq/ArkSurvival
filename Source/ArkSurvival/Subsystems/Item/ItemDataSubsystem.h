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

	void LoadAllItemTables();

	FConsumeItemData GetConsumableData(int32 ItemID) const;
	FEquipmentItemData GetEquipmentData(int32 ItemID) const;
	
	UPROPERTY()
	UDataTable* ConsumableDataTable = nullptr;
	
	UPROPERTY()
	UDataTable* EquipmentDataTable = nullptr;
	
	UPROPERTY()
	TMap<int32, FConsumeItemData> ConsumableDataMap = {};
	
	UPROPERTY()
	TMap<int32, FEquipmentItemData> EquipmentDataMap = {};
};
