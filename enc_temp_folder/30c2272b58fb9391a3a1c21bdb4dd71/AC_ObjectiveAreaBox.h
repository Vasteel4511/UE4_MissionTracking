// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mission/ObjectiveTracker.h"
#include "AC_ObjectiveAreaBox.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UAC_ObjectiveAreaBox : public UBoxComponent, public IObjectiveTracker
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	bool IsObjectiveComplete_Implementation() override;
	
	UFUNCTION()
	void OverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	bool HasPlayerEnteredBox;
};
