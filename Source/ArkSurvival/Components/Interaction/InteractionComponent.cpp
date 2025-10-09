#include "InteractionComponent.h"
#include "InteractableComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForInteractable();
}

void UInteractionComponent::CheckForInteractable()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	UCameraComponent* Camera = Character->FindComponentByClass<UCameraComponent>();
	if (!Camera)
	{
		return;
	}
	
	FVector Start = Camera->GetComponentLocation();
	FVector Forward = Camera->GetForwardVector();
	FVector End = Start + (Forward * TraceDistance);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(TraceRadius),
		QueryParams
	);
	
	if (bShowDebugTrace)
	{
		FColor TraceColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugSphere(GetWorld(), End, TraceRadius, 12, TraceColor, false, 0.0f);
		DrawDebugLine(GetWorld(), Start, End, TraceColor, false, 0.0f);

		if (bHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, TraceRadius, 12, FColor::Yellow, false, 0.0f);
		}
	}
	
	UInteractableComponent* NewInteractable = nullptr;

	if (bHit && HitResult.GetActor())
	{
		NewInteractable = HitResult.GetActor()->FindComponentByClass<UInteractableComponent>();
		
		if (NewInteractable && !NewInteractable->CanInteract(GetOwner()))
		{
			NewInteractable = nullptr;
		}
	}
	
	if (CurrentInteractable != NewInteractable)
	{
		CurrentInteractable = NewInteractable;

		// TODO : UI 업데이트
	}
}

void UInteractionComponent::TryInteract()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(GetOwner());
	}
}