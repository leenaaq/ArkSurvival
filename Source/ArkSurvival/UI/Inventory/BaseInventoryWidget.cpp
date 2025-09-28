#include "BaseInventoryWidget.h"
#include "Components/UniformGridPanel.h"

UBaseInventoryWidget::UBaseInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void UBaseInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeSlots();
}

void UBaseInventoryWidget::InitializeSlots()
{
	if (!InventoryGrid || !SlotWidgetClass)
	{
		return;
	}

	InventoryGrid->ClearChildren();
	SlotWidgets.Empty();

	 for (int32 i = 0; i < TotalSlots; ++i)
	 {
	 	UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
         
	 	if (SlotWidget)
	 	{
	 		SlotWidget->SetSlotIndex(i);
             
	 		int32 Row = i / SlotsPerRow;
	 		int32 Column = i % SlotsPerRow;
             
	 		InventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Column);
	 		SlotWidgets.Add(SlotWidget);
	 	}
	 }
}

void UBaseInventoryWidget::UpdateSlot(int32 SlotIndex, const FInventorySlot& SlotData)
{
	if (SlotWidgets.IsValidIndex(SlotIndex))
	{
		SlotWidgets[SlotIndex]->UpdateSlotData(SlotData);
	}
}

void UBaseInventoryWidget::RefreshAllSlots()
{
	if (!InventoryComponent) return;

	for (int32 i = 0; i < TotalSlots; ++i)
	{
		FInventorySlot SlotData = InventoryComponent->GetItem(i);
		UpdateSlot(i, SlotData);
	}
}
