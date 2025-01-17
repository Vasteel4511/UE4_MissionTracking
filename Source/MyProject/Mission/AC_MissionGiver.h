// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mission/Mission.h"
#include "AC_MissionGiver.generated.h"

class UAC_MissionTracker;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAC_MissionGiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_MissionGiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Mission")
	/** Mission that is available from this Mission Giver component, configured in editor */
	FMission AvailableMission;

	UFUNCTION(BlueprintCallable)
	/** Call this to transfer AvailableMission to the UUC_MissionTracker recipient */
	void GiveMission(UAC_MissionTracker* recipient);
	
};
