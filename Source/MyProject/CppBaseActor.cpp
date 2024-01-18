// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->InstanceName = MakeUniqueObjectName(NULL, ACppBaseActor::StaticClass(), TEXT("A_CppBase_C")).ToString();

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(this->Mesh);

}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	this->ShowActorInformation();
	this->InitialLocation = this->GetActorLocation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SinMovement();

}

// Debug info
void ACppBaseActor::ShowActorInformation()
{
	UE_LOG(LogTemp, Display, TEXT("Instance name: %s"), *this->InstanceName);
	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), this->EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("IsAlive: %s"), (this->IsAlive ? TEXT("true"): TEXT("false")));
}

void ACppBaseActor::SinMovement()
{
	UWorld* world = GetWorld();
	float delta = FMath::Sin(world->GetTimeSeconds() * this->Frequency) * this->Amplitude;
	this->SetActorLocation(FVector(this->InitialLocation[0], this->InitialLocation[1], this->InitialLocation[2] + delta));
}
