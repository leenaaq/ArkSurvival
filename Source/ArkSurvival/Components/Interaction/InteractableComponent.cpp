#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInteractableComponent::CanInteract_Implementation(AActor* Interactor) const
{
	if (!bCanInteract)
	{
		return false;
	}

	if (!Interactor)
	{
		return false;
	}
	
	return true;
}

void UInteractableComponent::Interact(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	OnInteracted.Broadcast(Interactor);
}