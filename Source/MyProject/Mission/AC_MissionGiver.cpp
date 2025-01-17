// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_MissionGiver.h"
#include "AC_MissionTracker.h"


// Sets default values for this component's properties
UAC_MissionGiver::UAC_MissionGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_MissionGiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_MissionGiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_MissionGiver::GiveMission(UAC_MissionTracker* recipient)
{
	/* recipient will usually be a UAC_MissionTracker component on the player */
	if (IsValid(recipient))
	{
		recipient->StartMission(AvailableMission);
	}
}

