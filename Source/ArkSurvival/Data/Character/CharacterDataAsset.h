#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

UCLASS()
class ARKSURVIVAL_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY()
	TSubclassOf<UAnimInstance> AnimBP;

	//Stats
	UPROPERTY()
	float MaxHealth = 0.f;

	UPROPERTY()
	float MovementSpeed = 0.f;
};
