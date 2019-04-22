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

	FindPhysicsHandle();

	SetupInputComp();
}

// Look for attached Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysHandler = GetOwner()->FindComponentByClass < UPhysicsHandleComponent>();
	if (PhysHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("We have a Physics Handle Component, Captain!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Physics Handle Component, Captain!"));
	}
}
// Look for attached Input Component
void UGrabber::SetupInputComp()
{
	InputComp = GetOwner()->FindComponentByClass <UInputComponent>();
	if (InputComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("We have an Input Component, Captain!"));
		// Bind an input action
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Input Component, Captain!"));
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

	// If the physics handle attached 
	if (PhysHandler->GrabbedComponent)
	{
		// move the object we're holding
		PhysHandler->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	// Line trace and see if we reach any actors with physics body colission channel set
	auto HitResult = GetFirstPhysBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto AcrorHit = HitResult.GetActor();
	// If we hit something then attach a physics handle
	if (AcrorHit)
	{
		// attach physics handle
		PhysHandler->GrabComponentAtLocation(
			ComponentToGrab, //ComponentToGrab
			NAME_None, //grab what bone name, if any
			ComponentToGrab->GetOwner()->GetActorLocation() //grab location
		);
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	// release physics handle
	PhysHandler->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysBodyInReach() const
{
	/// Get the player view point this tick
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);

	// Create a finish line of trace
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector()*Reach;

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

	return GrabberHit;
}

