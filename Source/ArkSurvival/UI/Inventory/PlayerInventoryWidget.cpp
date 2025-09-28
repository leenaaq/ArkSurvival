#include "PlayerInventoryWidget.h"
#include "ArkSurvival/Components/Inventory/PlayerInventoryComponent.h"

void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InventoryComponent = Cast<UPlayerInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UPlayerInventoryComponent::StaticClass()));
	RefreshAllSlots();
}
