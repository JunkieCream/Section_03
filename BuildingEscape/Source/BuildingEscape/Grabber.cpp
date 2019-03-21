// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Gameframework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

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
	
	// Look for attached Physics Handle
	PhysHandler = GetOwner()->FindComponentByClass < UPhysicsHandleComponent>();
	if (PhysHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("We have a Physics Handle Component, Captain!"), *ObjName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Physics Handle Component for %s, Captain!"), *ObjName);
	}

	// Look for attached Input Component
	InputComp = GetOwner()->FindComponentByClass <UInputComponent>();
	if (InputComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("We have an Input Component, Captain!"), *ObjName);
		// Bind an input action
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Input Component for %s, Captain!"), *ObjName);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get the player view point this tick
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);

	// Create a finish line of trace
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector()*Reach;
	// Draw red trace for
	DrawDebugLine(
		GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(255,0,0), false,0.f,0.f,10.f
	);

	/// Setup Query Parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line-trace (Ray-cast) out to reach distance
	FHitResult GrabberHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT GrabberHit, PlayerViewLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	/// See what we hit
	AActor* ActorThatHit = GrabberHit.GetActor();
	if (ActorThatHit)
	{
	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorThatHit->GetName());
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
}

