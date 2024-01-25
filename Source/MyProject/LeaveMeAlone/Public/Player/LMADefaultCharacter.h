// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MYPROJECT_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float _Orientation = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float _Velocity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool _Sprint = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float _Endurance = 0.0f;

private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void ZoomCamera(float Value);
	void DoSprint();
	void StopSprint();
};
