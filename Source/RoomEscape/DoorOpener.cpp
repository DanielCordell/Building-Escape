// Copyright Daniel Cordell 2018

#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	openable = GetOwner();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetPressurePlateMass() >= triggerMass) {
		isCurrentlyOpen = true;
		onOpenRequest.Broadcast();
	}
	else if (GetPressurePlateMass() < triggerMass && isCurrentlyOpen) {
		isCurrentlyOpen = false;
		OnCloseRequest.Broadcast();
	}
}


float UDoorOpener::GetPressurePlateMass() const {
	float totalMass = 0;

	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate Not Attatched to %s"), *GetOwner()->GetName());
		return totalMass;
	}
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(overlappingActors);

	for (const auto* actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}
