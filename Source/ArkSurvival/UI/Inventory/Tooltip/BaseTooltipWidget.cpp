#include "BaseTooltipWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UBaseTooltipWidget::UBaseTooltipWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBaseTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	HideWidget();
}

void UBaseTooltipWidget::SetTooltipData(const FInventorySlot& SlotData)
{
	CurrentSlotData = SlotData;
	UpdateTooltipUI();
}

void UBaseTooltipWidget::UpdateTooltipUI()
{
	if (!CurrentSlotData.ItemData.ItemName.IsEmpty())
	{
		if (ItemNameText)
		{
			ItemNameText->SetText(FText::FromString(CurrentSlotData.ItemData.ItemName));
		}
		
		if (ItemDescriptionText)
		{
			ItemDescriptionText->SetText(CurrentSlotData.ItemData.Description);
		}
		
		if (ItemIcon && CurrentSlotData.ItemData.Icon.IsValid())
		{
			UTexture2D* LoadedIcon = CurrentSlotData.ItemData.Icon.Get();
			if (LoadedIcon)
			{
				ItemIcon->SetBrushFromTexture(LoadedIcon);
			}
		}
		
		int32 ItemID = CurrentSlotData.ItemID;
		
		if (ConsumableSection)
		{
			ConsumableSection->SetVisibility(
				(ItemID >= 1000 && ItemID < 2000) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed
			);
		}

		if (EquipmentSection)
		{
			EquipmentSection->SetVisibility(
				(ItemID >= 2000 && ItemID < 3000) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed
			);
		}

		ShowWidget();
	}
	else
	{
		HideWidget();
	}
}

void UBaseTooltipWidget::UpdatePosition(FVector2D MousePosition)
{
	FVector2D Offset(10.0f, 10.0f);
	SetPositionInViewport(MousePosition + Offset);
}

void UBaseTooltipWidget::ShowWidget()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
	SetIsVisible(true);
}