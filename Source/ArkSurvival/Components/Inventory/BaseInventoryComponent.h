#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "ArkSurvival/Data/Item/BaseItemData.h"
#include "BaseInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct ARKSURVIVAL_API FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseItemData ItemData;

	FInventorySlot()
	{
		ItemID = 0;
		StackCount = 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARKSURVIVAL_API UBaseInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseInventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnRep_Slots();

	UFUNCTION(BlueprintCallable)
	bool AddItem(int32 ItemID, int32 Count = 1);

	UFUNCTION(BlueprintCallable)
	void RequestAddItem(int32 ItemID, int32 Count = 1);

	UFUNCTION(Server, Reliable)
	void Server_AddItem(int32 ItemID, int32 Count);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int32 ItemID, int32 Count = 1);

	UFUNCTION(BlueprintCallable)
	FInventorySlot GetItem(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable)
	bool CanAddItem(int32 ItemID, int32 Count = 1) const;

	UFUNCTION(BlueprintCallable)
	int32 GetEmptySlot() const;

private:
	void UpdateCurrentWeight();
	FBaseItemData GetItemDataByID(int32 ItemID) const;

public:
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Slots)
    TArray<FInventorySlot> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSlots = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWeight = 100.0f;

	UPROPERTY(BlueprintReadOnly, Replicated)
	float CurrentWeight = 0.0f;
};