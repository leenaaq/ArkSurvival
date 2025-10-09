#pragma once

#include "CoreMinimal.h"
#include "../BaseWidget.h"
#include "Slot/InventorySlotWidget.h"
#include "BaseInventoryWidget.generated.h"

class UUniformGridPanel;

UCLASS()
class ARKSURVIVAL_API UBaseInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UBaseInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeSlots();

	UFUNCTION(BlueprintCallable)
	void UpdateSlot(int32 SlotIndex, const struct FInventorySlot& SlotData);

	UFUNCTION(BlueprintCallable)
	void RefreshAllSlots();

protected:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* InventoryGrid = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotsPerRow = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalSlots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UInventorySlotWidget> SlotWidgetClass = nullptr;
	
	UPROPERTY()
	TArray<UInventorySlotWidget*> SlotWidgets = {};

	UPROPERTY(BlueprintReadWrite)
	UBaseInventoryComponent* InventoryComponent = nullptr;
};