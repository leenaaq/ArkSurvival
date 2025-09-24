#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterDataAsset;

UCLASS()
class ARKSURVIVAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

#pragma region Data
protected:
	void InitializeFromDataAsset();
	
protected:
	UPROPERTY(EditAnywhere)
	UCharacterDataAsset* CharacterDataAsset = nullptr;	
private:
	UPROPERTY(Replicated)
	float CurrentHealth = 0.f;
#pragma endregion

#pragma region Multi
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion
};
