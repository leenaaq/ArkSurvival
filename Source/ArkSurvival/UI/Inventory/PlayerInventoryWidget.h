#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryWidget.h"
#include "PlayerInventoryWidget.generated.h"

UCLASS()
class ARKSURVIVAL_API UPlayerInventoryWidget : public UBaseInventoryWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct();
};
