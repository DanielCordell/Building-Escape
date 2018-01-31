// Copyright Daniel Cordell 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

	UPROPERTY(BlueprintAssignable)
	FDoorRequest onOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnCloseRequest;

protected:
	// Called when the game starts
	void BeginPlay() override;

public:	
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetPressurePlateMass() const;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float triggerMass = 45.f;

	bool isCurrentlyOpen = false;

	AActor* openable = nullptr;
	UWorld* world = nullptr;
	
};
