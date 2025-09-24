#include "BaseCharacter.h"

#include "ArkSurvival/ArkSurvival.h"
#include "ArkSurvival/Data/Character/CharacterDataAsset.h"
#include "Net/UnrealNetwork.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeFromDataAsset();
}

#pragma region Data
void ABaseCharacter::InitializeFromDataAsset()
{
	ARK_VALIDATE(CharacterDataAsset);
	CurrentHealth = CharacterDataAsset->MaxHealth;
}
#pragma endregion


#pragma region Multi
void ABaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, CurrentHealth);
}
#pragma endregion
