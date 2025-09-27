#include "PlayerInventoryComponent.h"

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	MaxSlots = 300;
	MaxWeight = 100.0f;
}

bool UPlayerInventoryComponent::MoveItemToHotbar(int32 FromSlot, int32 ToHotbarSlot)
{
	return false;
}

FInventorySlot UPlayerInventoryComponent::GetHotbarItem(int32 HotbarSlot)
{
	if (HotbarSlot >= 0 && HotbarSlot < HotbarSlots)
	{
		return GetItem(HotbarSlot);
	}
    
	return FInventorySlot();
}