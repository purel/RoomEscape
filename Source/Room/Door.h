// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	float triggerMass = 30.f;

	AActor* Owner = nullptr;

	// return total mass over the trigger
	float GetTotalMassOver();
};
