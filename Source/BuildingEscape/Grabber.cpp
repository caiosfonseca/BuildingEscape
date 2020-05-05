// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

#define OUT

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

	FindPhysicsHandle();

	SetupInputComponent();
}


void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!IsValid(PhysicsHandle))
	{
		UE_LOG(LogTemp, Error, TEXT("The pawn %s doesn't have a UPhysicsHandleComponent"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(!IsValid(InputComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("The pawn %s doesn't have a UInputComponent"), *GetOwner()->GetName());
	}
	else
	{
		InputComponent->BindAction(FName(TEXT("Grab")), EInputEvent::IE_Pressed, this, &UGrabber::Grab );
		InputComponent->BindAction(FName(TEXT("Grab")), EInputEvent::IE_Released, this, &UGrabber::Release );
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed grab"));
	FHitResult Hit = GetFristPhysicsBodyInReach();
	// TODO only raycast when key is pressed and see if we reach any actors with a physics body collision channel set.
	// If we hit something, then attach the Physics Handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released grab"));
	// TODO Release physics handle
}

FHitResult UGrabber::GetFristPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
        );

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	bool bHasHit = GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
        );

	if(bHasHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit %s "), *Hit.GetActor()->GetName());
	}
	return Hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object we are holding 	
}