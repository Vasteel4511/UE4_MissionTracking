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

	if (HasMission && currentObjectiveTracker)
	{
		if (IObjectiveTracker::Execute_IsObjectiveComplete(currentObjectiveTracker))
		{
			CurrentMission.Objectives.RemoveAt(0);
			if (CurrentMission.Objectives.Num() > 0)
			{
				NextObjective();
			}
			else 
			{
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
	if (HasMission && CurrentMission.Objectives.Num() > 0 && IsValid(CurrentMission.Objectives[0].ObjectiveTrackingActor))
	{
		currentObjectiveTracker = nullptr;

		bool hasInterface = UKismetSystemLibrary::DoesImplementInterface(CurrentMission.Objectives[0].ObjectiveTrackingActor, UObjectiveTracker::StaticClass());
		
		if (hasInterface)
		{
			currentObjectiveTracker = CurrentMission.Objectives[0].ObjectiveTrackingActor;
		}
		else
		{
			TArray<UActorComponent*> components;
			CurrentMission.Objectives[0].ObjectiveTrackingActor->GetComponents(components);

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

		UE_LOG(LogTemp, Warning, TEXT("Mission: %s, Objective: %s, Description: %s"),
			*CurrentMission.Name.ToString(),
			*CurrentMission.Objectives[0].Name.ToString(),
			*CurrentMission.Objectives[0].Description.ToString());
	}
}
