#include "ItemSystemSettings.h"

UItemSystemSettings::UItemSystemSettings()
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("Item System");
}

const UItemSystemSettings* UItemSystemSettings::Get()
{
	return GetDefault<UItemSystemSettings>();
}