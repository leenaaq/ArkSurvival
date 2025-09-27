#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryComponent.h"
#include "PlayerInventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARKSURVIVAL_API UPlayerInventoryComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:
	UPlayerInventoryComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HotbarSlots = 10;

public:
	UFUNCTION(BlueprintCallable)
	bool MoveItemToHotbar(int32 FromSlot, int32 ToHotbarSlot);

	UFUNCTION(BlueprintCallable)
	FInventorySlot GetHotbarItem(int32 HotbarSlot);
};