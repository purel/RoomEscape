// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Door.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();

	void CloseDoor();
private:
	UPROPERTY(VisibleAnywhere)
	float openAngle = 80.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressTrigger;

	UPROPERTY(EditAnywhere)
	AActor *Player;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float triggerMass = 30.f;
	
	float lastOpenTime;

	AActor* Owner;

	// return total mass over the trigger
	float GetTotalMassOver();
};
