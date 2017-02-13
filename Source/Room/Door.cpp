// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "Door.h"


// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

	// find player
	Owner = GetOwner();
	if (!pressTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing pressure trigger volumn!"));
	}
}


// Called every frame
void UDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOver() > triggerMass)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
}

float UDoor::GetTotalMassOver()
{
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	if (!pressTrigger)
		return 0.f;
	pressTrigger->GetOverlappingActors(overlappingActors);
	for (const auto Actor : overlappingActors)
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	return totalMass;
}

