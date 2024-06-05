// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/InteractComponent.h"
#include "ShooterCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));

	RootComponent = InteractBox;

	WeaponMesh->SetupAttachment(RootComponent);

	InventoryComponent = nullptr;

	bPickedUp = false;

	bEquipped = false;

	CurrentAmmo = 120;

	bIsAmmoUnlimited = false;

	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AShooterCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Character)
	{
		InventoryComponent = Character->GetInventoryComponent();
	}
	
	
}

void AWeapon::StartShooting()
{
	GetWorldTimerManager().SetTimer(ShootHandle, this, &AWeapon::Shoot, ShootDelay, true);
}

void AWeapon::StopShooting()
{
	GetWorldTimerManager().ClearTimer(ShootHandle);
}



void AWeapon::Shoot()
{
	if (!bEquipped)
	{
		return;
	}

	

	if (CurrentAmmo > 0)
	{
		if (!bIsAmmoUnlimited)
			CurrentAmmo--;

		FHitResult Hit;

		FVector TraceStart = GetActorLocation();
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 2000.0f;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!bPickedUp)
	{
		AddActorWorldRotation(FRotator(0.0f, 1.0f, 0.0f));
	}
}

void AWeapon::OnInventoryUse()
{
	if (bEquipped)
	{
		Character->SetCurrentWeapon(nullptr);
		bEquipped = false;
		this->SetActorHiddenInGame(true);
	}
	else
	{
		Character->SetCurrentWeapon(this);
		bEquipped = true;
		this->SetActorHiddenInGame(false);
	}
}

const bool AWeapon::bIsWeaponEquipped() const
{
	return bEquipped;
}

void AWeapon::OnInteract(UInteractComponent* InteractedWith)
{
	if (InventoryComponent)
	{
		InventoryComponent->AddWeapon(this);
		bPickedUp = true;
		this->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
		this->SetActorRelativeLocation(FVector(0.0f, -30.0f, 15.0f));
		this->SetActorRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);

	}
}

class UTexture2D* AWeapon::GetInventoryIcon()
{
	return InventoryIcon;
}

