#pragma once

#include "CoreMinimal.h"
#include "../../BaseWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ArkSurvival/Components/Inventory/BaseInventoryComponent.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class ARKSURVIVAL_API UInventorySlotWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackCountText;

	UPROPERTY(BlueprintReadOnly)
	int32 SlotIndex = -1;

	UPROPERTY(BlueprintReadOnly)
	FInventorySlot SlotData;

public:
	UFUNCTION(BlueprintCallable)
	void SetSlotIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void UpdateSlotData(const FInventorySlot& NewSlotData);

	UFUNCTION(BlueprintCallable)
	void ClearSlot();

protected:
	UFUNCTION()
	void OnSlotClicked();

	void UpdateVisuals();
};