// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenDoor::OpenDoor(const float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DoorOpenSpeed * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find All overlapping actors
	if(IsValid(PressurePlate))
	{
		TArray<AActor*> OverlappingActors; 
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
		for(AActor* obj : OverlappingActors)
		{
			TotalMass += obj->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        }
	}
	// Add Up their masses

	return TotalMass;
}


void UOpenDoor::CloseDoor(const float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DoorCloseSpeed * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	if(!IsValid(PressurePlate))
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Open Door Component in it, but doesn't have any Pressure Plate!"), *GetOwner()->GetName());
	}

	if(!IsValid(ActorThatOpens))
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Open Door Component in it, but doesn't have any Actor that opens it!"), *GetOwner()->GetName());
	}
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(IsValid(PressurePlate) && IsValid(ActorThatOpens))
	{
		if(TotalMassOfActors() > MassToOpenDoors)
		{
			OpenDoor(DeltaTime);
			DoorLastOpened = GetWorld()->GetTimeSeconds();
		}
		else
		{
			if(GetWorld()->GetTimeSeconds() > DoorLastOpened + DoorCloseDelay)
			{
				CloseDoor(DeltaTime);
			}			
		}
	}
}

