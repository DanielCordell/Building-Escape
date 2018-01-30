// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();

	FString pos = Owner->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *Owner->GetName(), *pos);
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	auto Owner = GetOwner();
	FVector currentLocation = Owner->GetActorLocation();
	int i = rand() % 3;
	int mult = rand() % 2 == 0 ? -1 : 1;
	switch (i) {
	case 0: 
		currentLocation.X += 5 * mult;
		break;
	case 1:
		++currentLocation.Y += 5 * mult;
		break;
	default:
		++currentLocation.Z += 5 * mult;
		break;
	}
	Owner->SetActorLocation(currentLocation);


	// ...
}

