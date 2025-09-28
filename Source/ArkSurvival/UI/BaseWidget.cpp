#include "BaseWidget.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseWidget::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	SetIsVisible(true);
}

void UBaseWidget::HideWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetIsVisible(false);
}

void UBaseWidget::ToggleWidget()
{
	if (bIsVisible)
	{
		HideWidget();
	}
	else
	{
		ShowWidget();
	}
}
