#include "BaseInventoryComponent.h"
#include "ArkSurvival/Subsystems/Item/ItemDataSubsystem.h"

UBaseInventoryComponent::UBaseInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UBaseInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    
    Slots.SetNum(MaxSlots);
}

void UBaseInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UBaseInventoryComponent, Slots);
    DOREPLIFETIME(UBaseInventoryComponent, CurrentWeight);
}

bool UBaseInventoryComponent::AddItem(int32 ItemID, int32 Count)
{
    if (!CanAddItem(ItemID, Count))
    {
        return false;
    }
    
    FBaseItemData ItemData = GetItemDataByID(ItemID);
    
    for (FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID && Slot.StackCount > 0)
        {
            int32 MaxStack = ItemData.MaxStackSize;
            int32 CanAdd = MaxStack - Slot.StackCount;
            int32 AddAmount = FMath::Min(Count, CanAdd);
            
            Slot.StackCount += AddAmount;
            Count -= AddAmount;
            
            if (Count <= 0)
            {
                UpdateCurrentWeight();
                return true;
            }
        }
    }
    
    while (Count > 0)
    {
        int32 EmptySlot = GetEmptySlot();
        if (EmptySlot == -1)
        {
            return false;
        }
    
        int32 AddAmount = FMath::Min(Count, ItemData.MaxStackSize);
    
        Slots[EmptySlot].ItemID = ItemID;
        Slots[EmptySlot].StackCount = AddAmount;
        Slots[EmptySlot].ItemData = ItemData;
        Count -= AddAmount;
    }
    
    UpdateCurrentWeight();
    return true;
}

void UBaseInventoryComponent::RequestAddItem(int32 ItemID, int32 Count)
{
    if (GetOwner()->HasAuthority())
    {
        AddItem(ItemID, Count);
    }
    else
    {
        Server_AddItem(ItemID, Count);
    }
}

void UBaseInventoryComponent::Server_AddItem_Implementation(int32 ItemID, int32 Count)
{
    AddItem(ItemID, Count);
}

bool UBaseInventoryComponent::RemoveItem(int32 ItemID, int32 Count)
{
    for (FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID && Slot.StackCount > 0)
        {
            int32 RemoveAmount = FMath::Min(Count, Slot.StackCount);
            Slot.StackCount -= RemoveAmount;
            Count -= RemoveAmount;
            
            if (Slot.StackCount <= 0)
            {
                Slot.ItemID = 0;
                Slot.StackCount = 0;
            }
            
            if (Count <= 0)
            {
                UpdateCurrentWeight();
                return true;
            }
        }
    }
    
    UpdateCurrentWeight();
    return Count == 0;
}

FInventorySlot UBaseInventoryComponent::GetItem(int32 SlotIndex) const
{
    if (Slots.IsValidIndex(SlotIndex))
    {
        return Slots[SlotIndex];
    }
    
    return FInventorySlot();
}

bool UBaseInventoryComponent::CanAddItem(int32 ItemID, int32 Count) const
{
    FBaseItemData ItemData = GetItemDataByID(ItemID);
    if (ItemData.ItemName.IsEmpty())
    {
        return false;
    }
    
    float ItemWeight = ItemData.Weight * Count;
    
    return (CurrentWeight + ItemWeight) <= MaxWeight;
}

int32 UBaseInventoryComponent::GetEmptySlot() const
{
    for (int32 i = 0; i < Slots.Num(); ++i)
    {
        if (Slots[i].ItemID == 0 || Slots[i].StackCount <= 0)
        {
            return i;
        }
    }
    
    return -1;
}

void UBaseInventoryComponent::UpdateCurrentWeight()
{
    CurrentWeight = 0.0f;
    
    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.StackCount > 0)
        {
            CurrentWeight += Slot.ItemData.Weight * Slot.StackCount;
        }
    }
}

FBaseItemData UBaseInventoryComponent::GetItemDataByID(int32 ItemID) const
{
    UItemDataSubsystem* ItemDataSS = GetWorld()->GetGameInstance()->GetSubsystem<UItemDataSubsystem>();
    if (!ItemDataSS)
    {
        return FBaseItemData();
    }
    
    if (ItemID >= 1000 && ItemID < 2000)
    {
        FConsumeItemData ConsumeData = ItemDataSS->GetConsumableData(ItemID);
        return FBaseItemData(ConsumeData);
    }
    else if (ItemID >= 2000 && ItemID < 3000)
    {
        FEquipmentItemData EquipmentItemData = ItemDataSS->GetEquipmentData(ItemID);
        return FBaseItemData(EquipmentItemData);
    }
    
    return FBaseItemData();
}