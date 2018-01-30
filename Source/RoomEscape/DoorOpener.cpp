// Copyright Daniel Cordell 2018

#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}

void UDoorOpener::SetDoorRotation(float rotation) const {
	openable->SetActorRotation({ 0.f, rotation, 0.f });
}

// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	opener = world->GetFirstPlayerController()->GetPawn();
	openable = GetOwner();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(opener)) {
		lastOpenedTime = GetWorld()->GetTimeSeconds();
		OpenDoor();
	}

	if (world->GetTimeSeconds() - lastOpenedTime > closeDelay) {
		CloseDoor();
	}
}

