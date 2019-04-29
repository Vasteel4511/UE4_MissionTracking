// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_ObjectiveAreaBox.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

void UAC_ObjectiveAreaBox::BeginPlay()
{
	Super::BeginPlay();

	HasPlayerEnteredBox = false;

	OnComponentBeginOverlap.AddDynamic(this, &UAC_ObjectiveAreaBox::OverlapStart);
}

bool UAC_ObjectiveAreaBox::IsObjectiveComplete_Implementation()
{
	return HasPlayerEnteredBox;
}

void UAC_ObjectiveAreaBox::OverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player)
	{
		if (player == OtherActor)
		{
			HasPlayerEnteredBox = true;
		}
	}
}
