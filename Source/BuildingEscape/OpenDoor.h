// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	void OpenDoor(const float DeltaTime);

	void CloseDoor(const float DeltaTime);

	float TotalMassOfActors() const;

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Variables")
		float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Variables")
        float DoorOpenSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actors")
        class ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actors")
		class AActor* ActorThatOpens;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Variables")
		float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Variables")
        float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Variables")
		float MassToOpenDoors = 50.f;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float CurrentYaw = 0.f;
	float InitialYaw = 0.f;
	float DoorLastOpened = 0.f;
		
};
