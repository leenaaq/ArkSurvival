#include "ItemDataSubsystem.h"

#include "ArkSurvival/Data/Item/ConsumeItemData.h"
#include "ArkSurvival/Data/Item/EquipmentItemData.h"

void UItemDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ConsumableDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_Data/Item/DT_ConsumeItemData.DT_ConsumeItemData"));
	EquipmentDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_Data/Item/DT_EquipmentItemData.DT_EquipmentItemData"));

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

bool UItemDataSubsystem::IsValidConsumableID(int32 ItemID) const
{
	return ConsumableDataMap.Contains(ItemID);
}

bool UItemDataSubsystem::IsValidEquipmentID(int32 ItemID) const
{
	return EquipmentDataMap.Contains(ItemID);
}
