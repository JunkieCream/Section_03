// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

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
}

void UOpenDoor::DoorOpening()
{
	// Finding the owning Actor
	AActor *Owner = GetOwner();
	
	//Rotator creation
	FRotator ObjRotation(0, 0, 0);

	//Door rotation
	Owner->SetActorRotation(ObjRotation);
}

void UOpenDoor::DoorClosing()
{
	// Finding the owning Actor
	AActor *Owner = GetOwner();

	//Rotator creation
	FRotator ObjRotation(0,90,0);

	//Door rotation
	Owner->SetActorRotation(ObjRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume every frame	
	//Open the door when actor that could open is in Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		DoorOpening();
	}
	else
	{
		DoorClosing();
	}
}

