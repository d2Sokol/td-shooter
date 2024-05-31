#include "Components/InteractComponent.h"
#include "Components/BoxComponent.h"
#include "InteractInterface.h"
#include "ShooterCharacter.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PlayerCharacter = nullptr;


	

	
	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AShooterCharacter>(GetOwner());

	// ...

	
	
}

void UInteractComponent::sInteractUpdate()
{
	TArray<AActor*> OverlappingActors;

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	if (PlayerCharacter->GetInteractBox())
	{
		PlayerCharacter->GetInteractBox()->GetOverlappingActors(OverlappingActors);

		if (OverlappingActors.IsEmpty()) {
			return;
		}

		for (auto& Actor : OverlappingActors)
		{
			if (IInteractInterface* InteractableActor = Cast<IInteractInterface>(Actor))
			{
				InteractableActor->OnInteract(this);
			}
		}

	}
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	sInteractUpdate();
}


