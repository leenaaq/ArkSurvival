#include "InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (SlotButton && !SlotButton->OnClicked.IsAlreadyBound(this, &UInventorySlotWidget::OnSlotClicked))
	{
		SlotButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnSlotClicked);
	}
    
	ClearSlot();
}

void UInventorySlotWidget::SetSlotIndex(int32 Index)
{
	SlotIndex = Index;
}

void UInventorySlotWidget::UpdateSlotData(const FInventorySlot& NewSlotData)
{
	SlotData = NewSlotData;
	UpdateVisuals();
}

void UInventorySlotWidget::ClearSlot()
{
	SlotData = FInventorySlot();
	UpdateVisuals();
}

void UInventorySlotWidget::OnSlotClicked()
{
	// TODO 슬롯 클릭 처리
	UE_LOG(LogTemp, Warning, TEXT("Slot %d clicked"), SlotIndex);
}

void UInventorySlotWidget::UpdateVisuals()
{
	if (SlotData.StackCount > 0)
	{
		if (ItemIcon)
		{
			// TODO 아이콘 로드 및 표시
			ItemIcon->SetVisibility(ESlateVisibility::Visible);
		}
        
		if (StackCountText)
		{
			if (SlotData.StackCount > 1)
			{
				StackCountText->SetText(FText::AsNumber(SlotData.StackCount));
				StackCountText->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				StackCountText->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		if (ItemIcon)
		{
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		}
        
		if (StackCountText)
		{
			StackCountText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}