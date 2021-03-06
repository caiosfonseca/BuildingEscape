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
	FHitResult Hit = GetFristPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();

	if(IsValid(Hit.GetActor()))
	{
		// If we hit something, then attach the Physics Handle
		PhysicsHandle->GrabComponentAtLocation(
            ComponentToGrab,
            EName::NAME_None,
            GetPlayersReach()
            );
	}
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
        );
	
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayersWorldPos() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
        );

	return PlayerViewPointLocation;
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFristPhysicsBodyInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	bool bHasHit = GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        GetPlayersWorldPos(),
        GetPlayersReach(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
    );
	
	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	} 	
}