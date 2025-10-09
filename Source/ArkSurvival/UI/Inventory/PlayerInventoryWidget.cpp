#include "PlayerInventoryWidget.h"
#include "ArkSurvival/Components/Inventory/PlayerInventoryComponent.h"

void UPlayerInventoryWidget::NativeConstruct()
{
	InventoryComponent = Cast<UPlayerInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UPlayerInventoryComponent::StaticClass()));
	Super::NativeConstruct();
	RefreshAllSlots();
}
