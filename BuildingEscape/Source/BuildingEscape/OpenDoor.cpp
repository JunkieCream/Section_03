// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

#define OUT

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

	// Finding the owning Actor
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Pressure Plate!"));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume every frame	
	// Open the door when actor that could open is in Volume
	if (GetTotalMassOfActorsOnPlate() > 50.0)
	{
		DoorOpening();
	}
	else
	{
		DoorClosing();
	}
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// Find all overlaping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return 0; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them adding their masses to total mass
	for (auto& OverActor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressure plate"), *OverActor->GetName());
		TotalMass += OverActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UOpenDoor::DoorOpening()
{
	//Door rotation
	if (!Owner) { return; }
	OpenRequest.Broadcast();
}

void UOpenDoor::DoorClosing()
{
	//Door rotation
	if (!Owner) { return; }
	CloseRequest.Broadcast();
}

