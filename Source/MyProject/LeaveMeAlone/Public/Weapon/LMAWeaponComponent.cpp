// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "LMAWeaponComponent.h"
#include "LMAReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "LMABaseWeapon.h"

ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULMAWeaponComponent::Fire()
{
	if (Weapon)
	{
		Weapon->Fire();
	}
}

void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}


void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShootTimerActive)
	{
		ShootTimerValue += DeltaTime;
		Fire();
	}

}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(ALMABaseWeapon::StaticClass());
	if (IsValid(Weapon))
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "WeaponSocket");
		}
	}
}

void ULMAWeaponComponent::Reload()
{
	if (CanReload())
	{
		Weapon->ChangeClip();
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return !Weapon->IsCurrentClipFull();
}

void ULMAWeaponComponent::FirePressed()
{
  	ShootTimerActive = true;
}

void ULMAWeaponComponent::FireReleased()
{
    ShootTimerActive = false;
}

void ULMAWeaponComponent::ReloadPressed()
{
  	Reload();
}
