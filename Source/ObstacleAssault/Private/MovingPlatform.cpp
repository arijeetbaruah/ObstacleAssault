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
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector currentLocation = GetActorLocation();

	MovePlatform(currentLocation, DeltaTime);
	UpdateDirection(currentLocation, DeltaTime);
	
}

void AMovingPlatform::UpdateDirection(FVector currentLocation, float deltaTime)
{
	distance = FVector::Dist(startLocation, currentLocation);
	if (distance > maxDistance) {
		FVector movementDirection = (platformVelocity * direction).GetSafeNormal();
		startLocation += (movementDirection * distance);
		SetActorLocation(startLocation);
		direction *= -1;
	}
}

void AMovingPlatform::MovePlatform(FVector currentLocation, float deltaTime)
{
	currentLocation += (platformVelocity * deltaTime * direction);
	
	SetActorLocation(currentLocation);
}

