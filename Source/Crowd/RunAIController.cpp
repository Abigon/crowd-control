// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ARunAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Char = Cast<ACharacter>(InPawn);
}

void ARunAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckCharPosition();
}

void ARunAIController::CheckCharPosition()
{
	if (!GetPlayerChar() || !Char) return;

	const auto CharPosition = Char->GetActorLocation();
	
	if (bIsMoving && ((NextLocation - CharPosition).Size() <= MinDistanceToTarget))
	{
		bIsMoving = false;
	}

	if (!bIsMoving)
	{
		CheckPlayer();
	}
}

void ARunAIController::CheckPlayer()
{
	if (!GetPlayerChar() || !Char) return;
	
	const auto PlayerLocation = GetPlayerChar()->GetActorLocation();
	const auto CharPosition = Char->GetActorLocation();

	if ((PlayerLocation-CharPosition).Size() > MinDistanceToPlayer) return; 

	const auto NavSys = UNavigationSystemV1::GetCurrent(Char);
	if (!NavSys) return;

	NextLocation = GetNextPoint(NavSys, CharPosition, PlayerLocation);
	MoveToLocation(NextLocation, 20.f);
	bIsMoving = true;
}

FVector ARunAIController::GetNextPoint(const UNavigationSystemV1* NavSys, const FVector CharLoc, const FVector PlayerLoc)
{
	FNavLocation NavLocation;
	for(int32 i = 0; i < 100; ++i)
	{
		const auto Found = NavSys->GetRandomReachablePointInRadius(CharLoc, RunDistance, NavLocation);
		if (Found)
		{
			if ((PlayerLoc - NavLocation.Location).Size() >= MinDistanceToPlayer)
			{
				return NavLocation.Location;
			}
		}
	}
	return NavLocation.Location;
}

ACharacter* ARunAIController::GetPlayerChar()
{
	if (!PlayerChar) 
	{
		PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);
	}
	return PlayerChar;
}
