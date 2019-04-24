// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Functions for change door rotation
	void DoorOpening();
	void DoorClosing();

	// Function that count mass of all actors on trigger volume in kg
	float GetTotalMassOfActorsOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.2f;

	UPROPERTY(VisibleAnywhere)
	float CloseAngle = 90.0;

	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 0.0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	float LastDoorOpenTime;

	AActor* Owner;
};

