#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

class UBaseWidget;

UENUM(BlueprintType)
enum class EUIGroup : uint8
{
	HUD,
	Inventory,
	FullScreen,
	Popup
};

UENUM(BlueprintType)  
enum class EUICachePolicy : uint8
{
	AlwaysCache,
	CacheTemporary,
	NeverCache
};

UCLASS()
class ARKSURVIVAL_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void OpenUI(const FString& UIName);

	UFUNCTION(BlueprintCallable)
	void CloseUI(const FString& UIName);

	UFUNCTION(BlueprintCallable)
	void ToggleUI(const FString& UIName);

	UFUNCTION(BlueprintCallable)
	void CloseAllUI();

private:
	UPROPERTY()
	TMap<FString, UBaseWidget*> CachedWidgets;

	UPROPERTY()
	TArray<FString> ActiveUIStack;

	UPROPERTY(EditAnywhere)
	TMap<FString, EUIGroup> UIGroups;

	UPROPERTY(EditAnywhere)
	TMap<FString, EUICachePolicy> UICachePolicies;

	UPROPERTY(EditAnywhere)
	TMap<FString, TSubclassOf<UBaseWidget>> UIClasses;

	void CloseUIsByGroup(EUIGroup Group);
	UBaseWidget* GetOrCreateWidget(const FString& UIName);
	void CleanupTemporaryWidgets();
};