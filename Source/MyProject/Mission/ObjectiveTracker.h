// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveTracker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectiveTracker : public UInterface
{
	GENERATED_BODY()
};

/** Actors that need to be used as objective completion trackers need to implement this interface */
class MYPROJECT_API IObjectiveTracker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	/** return whhether the objective that the implementer is tracking is complete or not */
	bool IsObjectiveComplete();
};
