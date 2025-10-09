#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "../UI/Inventory/PlayerInventoryWidget.h"
#include "PlayerCharacter.generated.h"

class UInteractionComponent;
class UPlayerInventoryWidget;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UPlayerInventoryComponent;

UCLASS()
class ARKSURVIVAL_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	virtual void BeginPlay() override;

#pragma region Input
private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ToggleInventory(const FInputActionValue& Value);
	void TryInteract(const FInputActionValue& Value);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
#pragma endregion
	
#pragma region Components
private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(EditAnywhere)
	UPlayerInventoryComponent* PlayerInventoryComp = nullptr;

	UPROPERTY(EditAnywhere)
	UInteractionComponent* InteractionComp = nullptr;
	
#pragma endregion

#pragma region Preview
public:
	void CreateCharacterPreview();
	
private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<AActor> CharacterPreviewClass = nullptr;

	UPROPERTY()
	AActor* CharacterPreviewActor = nullptr;
#pragma endregion

};
