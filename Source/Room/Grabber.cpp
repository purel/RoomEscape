// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInput();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!pHandle)
		return;
	if (pHandle->GrabbedComponent)
	{
		pHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	//use line trace to check object within reach
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto hitActor = hitResult.GetActor();

	if (!pHandle)
		return;
	if(hitActor)
	pHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
}
void UGrabber::Release()
{
	if (!pHandle)
		return;
	pHandle->ReleaseComponent();
}
//Find physics handle
void UGrabber::FindPhysicsHandle()
{
	pHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (pHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
}
//find input component
void UGrabber::SetupInput()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Line-trace
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);

	AActor* actorHit = hit.GetActor();
	return hit;
}

FVector UGrabber::GetReachLineStart()
{
	FVector playerViewL;
	FRotator playerViewR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewL, playerViewR);
	return playerViewL;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector playerViewL;
	FRotator playerViewR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewL, playerViewR);
	return playerViewL + playerViewR.Vector() * reach;
}