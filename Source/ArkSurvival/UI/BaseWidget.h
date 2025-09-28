#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

UCLASS()
class ARKSURVIVAL_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBaseWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	
	void ShowWidget();
	
	void HideWidget();
	
	void ToggleWidget();
	
	void SetIsVisible(bool InIsVisible) { bIsVisible = InIsVisible; }

private:
	uint8 bIsVisible : 1 = 0;
};
