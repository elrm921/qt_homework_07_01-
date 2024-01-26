// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class  ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULMAWeaponComponent();

	void Reload();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UAnimMontage* ReloadMontage;

	/* manage the timer */
	FTimerHandle TimerHandle;

	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Fire();
    void FirePressed();
	void FireReleased();
	void ReloadPressed();

private:
	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;
	bool AnimReloading = false;
	bool ShootTimerActive = false;
	float ShootTimerValue = 0.0f;
	
	void SpawnWeapon();

	bool CanReload() const;
	bool CanReloadAnim() const;

};