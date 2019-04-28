// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Mission.generated.h"

USTRUCT(BlueprintType)
struct MYPROJECT_API FObjective
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Objective Config")
	FText Name;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Objective Config")
	FText Description;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Objective Config")
	AActor* ObjectiveTrackingActor;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYPROJECT_API FMission
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Objective Config")
	/** The name of this mission */
	FText Name;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Mission Config")
	/** The list of objectives that this mission consists of */
	TArray<FObjective> Objectives;
	

};
