#include "ItemDataSubsystem.h"

#include "ArkSurvival/Core/Settings/ItemSystemSettings.h"
#include "ArkSurvival/Data/Item/ConsumeItemData.h"
#include "ArkSurvival/Data/Item/EquipmentItemData.h"

void UItemDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UItemSystemSettings* Settings = UItemSystemSettings::Get();
    
	ConsumableDataTable = Settings->ConsumableDataTable.LoadSynchronous();
	EquipmentDataTable = Settings->EquipmentDataTable.LoadSynchronous();

	LoadAllItemTables();
}

void UItemDataSubsystem::LoadAllItemTables()
{
	ConsumableDataMap.Empty();
	EquipmentDataMap.Empty();

	// 소비템
	if (IsValid(ConsumableDataTable))
	{
		TArray<FName> RowNames = ConsumableDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FConsumeItemData* RowData = ConsumableDataTable->FindRow<FConsumeItemData>(RowName, TEXT(""));
			if (RowData)
			{
				int32 ItemID = FCString::Atoi(*RowName.ToString());
				ConsumableDataMap.Add(ItemID, *RowData);
			}
		}
	}

	// 장비
	if (IsValid(EquipmentDataTable))
	{
		TArray<FName> RowNames = EquipmentDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FEquipmentItemData* RowData = EquipmentDataTable->FindRow<FEquipmentItemData>(RowName, TEXT(""));
			if (RowData)
			{
				int32 ItemID = FCString::Atoi(*RowName.ToString());
				EquipmentDataMap.Add(ItemID, *RowData);
			}
		}
	}
}

FConsumeItemData UItemDataSubsystem::GetConsumableData(int32 ItemID) const
{
	if (ConsumableDataMap.Contains(ItemID))
	{
		return ConsumableDataMap[ItemID];
	}
	return FConsumeItemData();
}

FEquipmentItemData UItemDataSubsystem::GetEquipmentData(int32 ItemID) const
{
	if (EquipmentDataMap.Contains(ItemID))
	{
		return EquipmentDataMap[ItemID];
	}
	return FEquipmentItemData();
}