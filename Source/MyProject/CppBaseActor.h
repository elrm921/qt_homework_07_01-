// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

UCLASS()
class MYPROJECT_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	FString InstanceName;
	UPROPERTY(EditAnywhere)
	int EnemyNum;
	UPROPERTY(EditAnywhere)
	bool IsAlive;

	UPROPERTY(EditAnywhere)
	float Amplitude;
	UPROPERTY(EditAnywhere)
	float Frequency;
	UPROPERTY(VisibleAnywhere)
	FVector InitialLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	void SinMovement();

private:
	// Debug info
	void ShowActorInformation();

};
