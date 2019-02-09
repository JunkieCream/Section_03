// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
//#include "Engine/World.h"
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

	void DoorOpening();
	void DoorClosing();

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
	
	AActor* ActorThatOpens;

	AActor *Owner;
};
