// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletStartPosition = CreateDefaultSubobject<USceneComponent>("Bullet Start");
	BulletStartPosition->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABaseCharacter::Fire(const FVector& FireAtLocation)
{
	if(!HasWeapon()) return false;
	return WeaponComponent->Fire(BulletStartPosition->GetComponentLocation(), FireAtLocation);
}

int ABaseCharacter::CheckWeaponAmmo()
{
	if(!HasWeapon()) return false;
	return WeaponComponent->CheckAmmoRemaining();
}

bool ABaseCharacter::Reload()
{
	if(!HasWeapon()) return false;
	WeaponComponent->Reload();
	return true;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool ABaseCharacter::HasWeapon()
{
	if(WeaponComponent != nullptr)
	{
		return true;
	}
	return false;
}

void ABaseCharacter::EquipWeapon(bool bEquipWeapon, const FWeaponStats& PickupWeaponStats)
{
	if (bEquipWeapon && !HasWeapon())
	{
		WeaponComponent = NewObject<UWeaponComponent>(this);
		WeaponComponent->RegisterComponent();
		WeaponComponent->SetWeaponStats(PickupWeaponStats);
		WeaponComponent->Reload();
		UE_LOG(LogTemp, Display, TEXT("Player has equipped weapon."))
	}
	else if (!bEquipWeapon && HasWeapon())
	{
		WeaponComponent->UnregisterComponent();
		WeaponComponent = nullptr;
		UE_LOG(LogTemp, Display, TEXT("Player has unequipped weapon."))
	}
	EquipWeaponGraphical(bEquipWeapon);
} 

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}