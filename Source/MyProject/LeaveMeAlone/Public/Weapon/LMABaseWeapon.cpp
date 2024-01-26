// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

ALMABaseWeapon::ALMABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(GetRootComponent());

	/* 
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/FPWeapon/Mesh/SK_FPGun"));
	WeaponMesh->SetStaticMesh(MeshObj.Object);
	*/
}

void ALMABaseWeapon::Fire()
{
	Shoot();
}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}

	DecrementBullets();
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));

	if (IsCurrentClipEmpty())
	{
		ChangeClip();
		AlertNoBullets();
	}
	
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets==0;
}

bool ALMABaseWeapon::IsCurrentClipFull() const
{
	return CurrentAmmoWeapon.Bullets==30;
}

void ALMABaseWeapon::ChangeClip()
{
	UE_LOG(LogWeapon, Display, TEXT("Reloading"));
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

void ALMABaseWeapon::AlertNoBullets()
{
	UE_LOG(LogWeapon, Display, TEXT("AlertNoBullets"));
}


void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}