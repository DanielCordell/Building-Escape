// Copyright Daniel Cordell 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

	//Lets us potentially have multiple states of rotation in the future;
	void SetDoorRotation(float rotation) const;
	void CloseDoor() const { SetDoorRotation(openAngle); }
	void OpenDoor() const { SetDoorRotation(closedAngle); }

protected:
	// Called when the game starts
	void BeginPlay() override;

public:	
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetPressurePlateMass() const;

private:
	UPROPERTY(EditAnywhere)
	float openAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float closedAngle = 20.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere) 
	float closeDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float triggerMass = 45.f;

	float lastOpenedTime = 0.f;

	AActor* openable = nullptr;
	UWorld* world = nullptr;
	
};
