// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_ObjectiveAreaBox.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

void UAC_ObjectiveAreaBox::BeginPlay()
{
	Super::BeginPlay();

	IsPlayerInArea = false;

	// this binds our two functions to the UE4 collision system as far as this box is concerned
	OnComponentBeginOverlap.AddDynamic(this, &UAC_ObjectiveAreaBox::OverlapStart);
	OnComponentEndOverlap.AddDynamic(this, &UAC_ObjectiveAreaBox::OverlapEnd);
}

/** Since the point of this component is to decide whether an objective is complete or not
  * depending on whether the player has reached a given area, all we do is return true or
  * false is the player in the box. */
bool UAC_ObjectiveAreaBox::IsObjectiveComplete_Implementation()
{
	return IsPlayerInArea;
}

/** When something overlaps this box component */
void UAC_ObjectiveAreaBox::OverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// get hold of the player character
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// if ^ that worked ok...
	if (player)
	{
		//...check to see if 'player' is the thing that overlapped us...
		if (player == OtherActor)
		{
			//...then set this flag is so.
			IsPlayerInArea = true;
		}
	}
}

/** When something stops overlapping this box component */
void UAC_ObjectiveAreaBox::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// get hold of the player character
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// if ^ that worked ok...
	if (player)
	{
		//...check to see if 'player' is the thing that stopped overlapping us...
		if (player == OtherActor)
		{
			//...then unset this flag is so.
			IsPlayerInArea = false;
		}
	}
}
