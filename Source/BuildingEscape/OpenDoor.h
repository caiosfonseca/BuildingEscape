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

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Yaw")
		float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Yaw")
        float Velocity = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Yaw")
        class ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Yaw")
		class AActor* ActorThatOpens;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float CurrentYaw = 0.f;
	float InitialYaw = 0.f;
		
};
