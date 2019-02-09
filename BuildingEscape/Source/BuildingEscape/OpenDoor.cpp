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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Finding the owning Actor
	Owner = GetOwner();
}

void UOpenDoor::DoorOpening()
{
	//Door rotation
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::DoorClosing()
{
	//Door rotation
	Owner->SetActorRotation(FRotator(0, CloseAngle, 0));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume every frame	
	//Open the door when actor that could open is in Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		DoorOpening();
	}
	else if ((LastDoorOpenTime+DoorCloseDelay)<=GetWorld()->GetTimeSeconds())
	{
		DoorClosing();
	}
	
}

