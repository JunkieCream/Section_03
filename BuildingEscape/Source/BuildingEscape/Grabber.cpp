// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Just report
	FString ObjName = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty on %s!"), *ObjName);
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point this tick
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);
	// TODO Log out to test
	UE_LOG(LogTemp, Warning, TEXT("Location: %s Position: %s"), 
		*PlayerViewLocation.ToString(),
		*PlayerViewRotation.ToString()
	);

	// Ray-cast out to reach distance

	// See what we hit
}

