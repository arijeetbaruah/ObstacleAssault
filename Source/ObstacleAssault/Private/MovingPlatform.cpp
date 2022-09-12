// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	direction = 1;
	startLocation = GetActorLocation();
	FString playerName = GetName();

	UE_LOG(LogTemp, Display, TEXT("Name: %s"), *playerName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	UpdateDirection(DeltaTime);
	UpdateRotation(DeltaTime);
	
}

void AMovingPlatform::UpdateDirection(float deltaTime)
{
	distance = GetMovedDistance();
	if (ShouldPlatformReturn()) {
		FVector movementDirection = (platformVelocity * direction).GetSafeNormal();
		startLocation += (movementDirection * distance);
		SetActorLocation(startLocation);
		direction *= -1;
	}
}

void AMovingPlatform::UpdateRotation(float deltaTime)
{
	AddActorLocalRotation(platformRotation * deltaTime);
}

void AMovingPlatform::MovePlatform(float deltaTime)
{
	FVector currentLocation = GetActorLocation();
	currentLocation += (platformVelocity * deltaTime * direction);
	
	SetActorLocation(currentLocation);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return distance > maxDistance;
}

float AMovingPlatform::GetMovedDistance() const
{
	return FVector::Dist(startLocation, GetActorLocation());
}

