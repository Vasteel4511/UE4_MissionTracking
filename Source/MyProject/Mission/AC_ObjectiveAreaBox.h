// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mission/ObjectiveTracker.h"
#include "AC_ObjectiveAreaBox.generated.h"

/**
 * This actor component is an extension of the built in UE4 BoxComponent that implements
 * the IObjectiveTracker interface. This means it gets the IsObjectiveComplete function
 * and can be used to track mission objective progress. In this case the IsObjectiveComplete
 * function returns true if the player is inside the box.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UAC_ObjectiveAreaBox : public UBoxComponent, public IObjectiveTracker
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	// the function we get from the IObjectiveTracker interface.
	// it has _Implementation after its name because UE4 is wierd like that sometimes!
	bool IsObjectiveComplete_Implementation() override;
	
	// The function we want to call when something starts overlapping this component.
	// This is bound to the UE4 collision system in BeginPlay()
	UFUNCTION()
	void OverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// The function we want to call when something stops overlapping this component.
	// This is bound to the UE4 collision system in BeginPlay()
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	// keeps track of whether player is in the box.
	// this is what IsObjectiveComplete returns.
	bool IsPlayerInArea;
};
