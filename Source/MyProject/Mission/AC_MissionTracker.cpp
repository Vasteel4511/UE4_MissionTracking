// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_MissionTracker.h"
#include <Kismet/KismetSystemLibrary.h>


// Sets default values for this component's properties
UAC_MissionTracker::UAC_MissionTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_MissionTracker::BeginPlay()
{
	Super::BeginPlay();

	HasMission = false;
	currentObjectiveTracker = nullptr;
}


// Called every frame
void UAC_MissionTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// do we have a mission and a valid object to track current objective completion
	// (the latter is set below in NextObjective)
	if (HasMission && currentObjectiveTracker)
	{
		// this should return true if the current objective is complete.
		// the exact implementation of IsObjectiveComplete can be anything we need e.g. player
		// has reached a certain area, killed so many things etc
		if (IObjectiveTracker::Execute_IsObjectiveComplete(currentObjectiveTracker))
		{
			/** current objective is complete */

			// remove the current objective from our mission
			CurrentMission.Objectives.RemoveAt(0);

			// if we still have objective in the mission, start the next one
			if (CurrentMission.Objectives.Num() > 0)
			{
				NextObjective();
			}
			else 
			{
				/** no more objectives, mission is over */

				UE_LOG(LogTemp, Warning, TEXT("Mission Complete"));
				HasMission = false;
				currentObjectiveTracker = nullptr;
			}
		}
	}
}

void UAC_MissionTracker::StartMission(FMission mission)
{
	CurrentMission = mission;
	HasMission = true;

	NextObjective();
}

void UAC_MissionTracker::NextObjective()
{
	/** We need to work out which object is responsible for tracking whether the current 
	    objective is complete or not */

	// do we have a mission, an objective, and an object to track that objective?
	if (HasMission && CurrentMission.Objectives.Num() > 0 && IsValid(CurrentMission.Objectives[0].ObjectiveTrackingActor))
	{
		// start by setting this to null, it we get set to the correct object below
		currentObjectiveTracker = nullptr;

		// check whether the tracking actor for the current objective (both set in editor) implements the ObjectiveTracker interface...
		bool hasInterface = UKismetSystemLibrary::DoesImplementInterface(CurrentMission.Objectives[0].ObjectiveTrackingActor, UObjectiveTracker::StaticClass());
		
		if (hasInterface)
		{
			//...it did, so set this as the currentObjectiveTracker and we are done here.
			currentObjectiveTracker = CurrentMission.Objectives[0].ObjectiveTrackingActor;
		}
		else
		{
			//...it did not, so check each component of the tracking actor to see if any implement the ObjectiveTracker interface

			// get all components attached to the objective tracker actor
			TArray<UActorComponent*> components;
			CurrentMission.Objectives[0].ObjectiveTrackingActor->GetComponents(components);

			// loop over the components, if we find one that implements the ObjectiveTracker interface then
			// set that component as the currentObjectiveTracker and we are done.
			for (int i = 0; i < components.Num(); ++i)
			{
				hasInterface = UKismetSystemLibrary::DoesImplementInterface(components[i], UObjectiveTracker::StaticClass());
				if (hasInterface)
				{
					currentObjectiveTracker = components[i];
					break;
				}
			}
		}

		// write the current objective to the output log
		UE_LOG(LogTemp, Warning, TEXT("Mission: %s, Objective: %s, Description: %s"),
			*CurrentMission.Name.ToString(),
			*CurrentMission.Objectives[0].Name.ToString(),
			*CurrentMission.Objectives[0].Description.ToString());
	}
}
