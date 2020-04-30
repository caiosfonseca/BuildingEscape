// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = StartingYaw + TargetYaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);
	Alpha = FMath::Clamp(Alpha + DeltaTime/8.f, 0.f, 1.f);
	FRotator NewRot{GetOwner()->GetActorRotation()};
	NewRot.Yaw = FMath::Lerp(GetOwner()->GetActorRotation().Yaw, TargetYaw, Alpha);
	// If we want linear interpolation instead of Exponential, we have to change the current yaw for StartingYaw	
	GetOwner()->SetActorRotation(NewRot);

	// ...
}

