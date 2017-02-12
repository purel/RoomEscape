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

	// 
	Owner = GetOwner();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOver() > triggerMass)
	{
		OpenDoor();
		lastOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - lastOpenTime >= doorCloseDelay)
		CloseDoor();

}

void UDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

void UDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

float UDoor::GetTotalMassOver()
{
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	pressTrigger->GetOverlappingActors(overlappingActors);
	for (const auto Actor : overlappingActors)
	{
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("The total mass is: %f"), totalMass);
	}
	
	return totalMass;
}

