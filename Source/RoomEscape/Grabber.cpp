// Copyright Daniel Cordell 2018

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindInputComponent();
	FindPhysicsComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(GetEndOfReach());
	}

}

void UGrabber::Grab() {
	FHitResult result = GetFirstPhysicsBodyInReach();
	auto grabable = result.GetComponent();
	AActor* actorHit = result.GetActor();

	if (actorHit) {
		physicsHandle->GrabComponent(grabable, NAME_None, grabable->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release() {
	physicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsComponent() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle Not Found in %s"), *(GetOwner()->GetName()));
	}

}

void UGrabber::FindInputComponent() {
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Not Found in %s"), *(GetOwner()->GetName()));
	}
	else {
		inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);

	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
#
	FHitResult hit;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams objectParams(ECC_PhysicsBody);
	GetWorld()->LineTraceSingleByObjectType(hit, GetStartOfReach(), GetEndOfReach(), objectParams, traceParams);

	return hit;
}

const FVector UGrabber::GetEndOfReach() const
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
	return location + rotation.Vector() * reach;
}

const FVector UGrabber::GetStartOfReach() const
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
	return location;
}

