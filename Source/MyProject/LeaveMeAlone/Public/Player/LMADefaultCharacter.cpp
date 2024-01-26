// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Weapon/LMAWeaponComponent.h"
#include "../Weapon/LMABaseWeapon.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = ArmLength;
	SpringArm->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f)); 
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;


	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(FOV);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CurrentWeapon = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
	
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		_Orientation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, _Orientation, 0.0f)));
	}

	if (GetVelocity().IsZero()) _Velocity = 0.0f;
	else _Velocity = 50.0f;

	if (_Sprint) _Endurance -= DeltaTime;
	else _Endurance += DeltaTime;

	if (_Endurance > 5.00f) _Endurance = 5.00f;
	if (_Endurance < 0.00f) _Endurance = 0.00f;

}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ALMADefaultCharacter::ZoomCamera);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::DoSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALMADefaultCharacter::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ALMADefaultCharacter::FireReleased);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALMADefaultCharacter::ReloadPressed);
	
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::ZoomCamera(float Value)
{
	SpringArm->TargetArmLength += Value * 100;
	if (SpringArm->TargetArmLength > 1500.0f) SpringArm->TargetArmLength = 1500.0f;
	if (SpringArm->TargetArmLength < 500.0f) SpringArm->TargetArmLength = 500.0f;
}

void ALMADefaultCharacter::DoSprint()
{
	UE_LOG(LogTemp, Display, TEXT("DoSprint"));
	_Sprint = true;

}

void ALMADefaultCharacter::StopSprint()
{
	UE_LOG(LogTemp, Display, TEXT("StopSprint"));
	_Sprint = false;

}

void ALMADefaultCharacter::FirePressed()
{
	UE_LOG(LogTemp, Display, TEXT("FirePressed"));
	CurrentWeapon->FirePressed();
}

void ALMADefaultCharacter::FireReleased()
{
	UE_LOG(LogTemp, Display, TEXT("ReloadReleased"));
	CurrentWeapon->FireReleased();
}

void ALMADefaultCharacter::ReloadPressed()
{
	UE_LOG(LogTemp, Display, TEXT("ReloadPressed"));
	CurrentWeapon->ReloadPressed();
}
