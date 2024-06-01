// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Weapon.generated.h"

class UBoxComponent;
class UInventoryComponent;

UCLASS()
class TD_SHOOTER_API AWeapon : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInventoryUse();

	const bool bIsWeaponEquipped() const;

	virtual void OnInteract(UInteractComponent* InteractedWith) override;

	class UTexture2D* GetInventoryIcon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bEquipped;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	class UTexture2D* InventoryIcon;
private:	

	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractBox;
	
	void Shoot();
};
