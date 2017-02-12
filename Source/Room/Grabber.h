// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;



private:
	//How far can reach
	float reach = 100.f;

	UPhysicsHandleComponent *pHandle = nullptr;

	UInputComponent *input = nullptr;

	// called when input captured
	void Grab();
	//called when input released
	void Release();

	void FindPhysicsHandle();
	void SetupInput();

	// get first object hit within reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// returns player location
	FVector GetReachLineStart();
	// returns end of reach line
	FVector GetReachLineEnd();
};
