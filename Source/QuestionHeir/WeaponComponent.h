// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UENUM()
enum EWeaponType:uint8
{
	Rifle,
	Pistol
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType = EWeaponType::Rifle;
	float Accuracy = 1.0f;
	float FireRate = 0.2f;
	float BaseDamage = 10.0f;
	int32 MagazineSize = 5;
	float ReloadTime = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTIONHEIR_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FWeaponStats WeaponStats;
	int32 RoundsRemainingInMagazine;
	float TimeSinceLastShot = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Fire(const FVector& BulletStart, const FVector& FireAtLocation);

	void Reload();

	void CompleteReload();

	int CheckAmmoRemaining() const;

	void SetWeaponStats(const FWeaponStats& NewStats);

private:
	int ShotsLeft;
		
};
