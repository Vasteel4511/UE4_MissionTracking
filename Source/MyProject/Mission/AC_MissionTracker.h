// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mission/Mission.h"
#include "ObjectiveTracker.h"
#include "AC_MissionTracker.generated.h"

/** This actor component should be attached to anything that needs to keep track
  * of the progress of a mission. Player will have one of these components */
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAC_MissionTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_MissionTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** The mission we are currently on */
	FMission CurrentMission;

	/** Do we have a mission at the moment? */
	bool HasMission;

	/** Sets the above two variables and calls NextObjective */
	void StartMission(FMission mission);

private:

	/** Works out what object is tracking whether the current objective is complete
	    and stores a pointer to it in the below variable */
	void NextObjective();

	/** can be any object, but will typically be an actor or actor component, that implements
	    the IObjectiveTracker interface */
	UObject* currentObjectiveTracker;
};
