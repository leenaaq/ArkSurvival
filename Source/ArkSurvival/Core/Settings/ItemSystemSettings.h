#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemSystemSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Item System Settings"))
class ARKSURVIVAL_API UItemSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UItemSystemSettings();
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Data Tables")
	TSoftObjectPtr<UDataTable> ConsumableDataTable = nullptr;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Data Tables")
	TSoftObjectPtr<UDataTable> EquipmentDataTable = nullptr;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Item ID Ranges")
	int32 ConsumableIDMin = 1000;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Item ID Ranges")
	int32 ConsumableIDMax = 1999;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Item ID Ranges")
	int32 EquipmentIDMin = 2000;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Item ID Ranges")
	int32 EquipmentIDMax = 2999;
	
	static const UItemSystemSettings* Get();
};