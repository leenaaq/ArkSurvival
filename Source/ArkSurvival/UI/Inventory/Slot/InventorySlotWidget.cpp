#include "InventorySlotWidget.h"

#include "ArkSurvival/UI/Inventory/Tooltip/BaseTooltipWidget.h"
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
    
	if (SlotButton)
	{
		if (!SlotButton->OnClicked.IsAlreadyBound(this, &UInventorySlotWidget::OnSlotClicked))
		{
			SlotButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnSlotClicked);
		}
		
		SlotButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnSlotHovered);
		SlotButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnSlotUnhovered);
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
			if (SlotData.ItemData.Icon.IsValid())
			{
				UTexture2D* LoadedIcon = SlotData.ItemData.Icon.Get();
				if (LoadedIcon)
				{
					ItemIcon->SetBrushFromTexture(LoadedIcon);
					ItemIcon->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					ItemIcon->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else
			{
				ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			}
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

void UInventorySlotWidget::OnSlotHovered()
{
	if (SlotData.StackCount > 0 && TooltipWidgetClass)
	{
		if (!ItemTooltipWidget)
		{
			ItemTooltipWidget = CreateWidget<UBaseTooltipWidget>(GetWorld(), TooltipWidgetClass);
			if (ItemTooltipWidget)
			{
				ItemTooltipWidget->AddToViewport(999);
			}
		}

		if (ItemTooltipWidget)
		{
			ItemTooltipWidget->SetTooltipData(SlotData);
		}
	}
}

void UInventorySlotWidget::OnSlotUnhovered()
{
	if (ItemTooltipWidget)
	{
		ItemTooltipWidget->HideWidget();
	}
}