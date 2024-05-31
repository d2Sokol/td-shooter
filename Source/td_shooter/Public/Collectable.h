// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Collectable.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UInteractComponent;

UCLASS()
class TD_SHOOTER_API ACollectable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(UInteractComponent* InteractedWith) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractBox;
};
