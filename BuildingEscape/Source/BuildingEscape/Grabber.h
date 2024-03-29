// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Length of grabber
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysHandler = nullptr;
	UInputComponent* InputComp = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// When grab button released
	void Release();

	// Look for physics handle component
	void FindPhysicsHandle();

	// Setup attached input component
	void SetupInputComp();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysBodyInReach();

	// Return the location of grab point
	FVector GetLineEnd();

	FVector GetLineStart();
};
