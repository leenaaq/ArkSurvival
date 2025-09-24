#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

UCLASS()
class ARKSURVIVAL_API UCharacterDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    USkeletalMesh* SkeletalMesh = nullptr;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UAnimInstance> AnimBP = nullptr;

    UPROPERTY(EditAnywhere)
    float MaxHealth = 0.f;

    UPROPERTY(EditAnywhere)
    float MovementSpeed = 0.f;
};