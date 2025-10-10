#pragma once

#include "CoreMinimal.h"
#include "../../BaseWidget.h"
#include "ArkSurvival/Components/Inventory/BaseInventoryComponent.h"
#include "BaseTooltipWidget.generated.h"

UCLASS()
class ARKSURVIVAL_API UBaseTooltipWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UBaseTooltipWidget(const FObjectInitializer& ObjectInitializer);

	virtual void ShowWidget() override;
	
	UFUNCTION(BlueprintCallable)
	void SetTooltipData(const FInventorySlot& SlotData);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePosition(FVector2D MousePosition);

protected:
	virtual void NativeConstruct() override;

	void UpdateTooltipUI();
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDescriptionText = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* ConsumableSection = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* EquipmentSection = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FInventorySlot CurrentSlotData = FInventorySlot();
};