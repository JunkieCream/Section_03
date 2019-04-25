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

/// Look for attached Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysHandler = GetOwner()->FindComponentByClass <UPhysicsHandleComponent>();
	if (PhysHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Physics Handle Component, Captain!"));
	}
}
/// Look for attached Input Component
void UGrabber::SetupInputComp()
{
	InputComp = GetOwner()->FindComponentByClass <UInputComponent>();
	if (InputComp)
	{
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

	// If the physics handle attached 
	if (!PhysHandler) { return; }
	if (PhysHandler->GrabbedComponent)
	{
		// move the object we're holding
		PhysHandler->SetTargetLocation(GetLineEnd());
	}
}

void UGrabber::Grab()
{
	// Line trace and see if we reach any actors with physics body colission channel set
	auto HitResult = GetFirstPhysBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto AcrorHit = HitResult.GetActor();

	// If we hit something then attach a physics handle
	if (AcrorHit)
	{
		if (!PhysHandler) { return; }
		PhysHandler->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(), //grab location
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	if (!PhysHandler) { return; }
	PhysHandler->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysBodyInReach()
{
	/// Line-trace (Ray-cast) out to reach distance
	FHitResult GrabberHit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT GrabberHit, GetLineStart(), GetLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return GrabberHit;
}

FVector UGrabber::GetLineStart()
{
	/// Get the player view point this tick
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);
	return PlayerViewLocation;
}

FVector UGrabber::GetLineEnd()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);
	return PlayerViewLocation + PlayerViewRotation.Vector()*Reach;
}