// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRunComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UAIRunComponent::UAIRunComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIRunComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);

	MyController = Cast<AAIController>(GetOwner());
	if (MyController)
	{
		MyPawn = MyController->GetCharacter(); 
	}
}

void UAIRunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckPawn();
	CheckCharPosition();
}

void UAIRunComponent::CheckCharPosition()
{
	if (!PlayerChar || !MyPawn || !MyController) return;

	const auto PawnPosition = MyPawn->GetActorLocation();
	const float PawnSpeed = MyPawn->GetVelocity().Size();
	
	if (bIsMoving && (((NextLocation - PawnPosition).Size() <= MinDistanceToTarget) || (PawnSpeed == 0)))
	{
		bIsMoving = false;
	}

	if (bIsMoving) return;

	const auto PlayerLocation = PlayerChar->GetActorLocation();

	if ((PlayerLocation-PawnPosition).Size() > MinDistanceToPlayer) return; 

	const auto NavSys = UNavigationSystemV1::GetCurrent(MyPawn);
	if (!NavSys) return;

	NextLocation = GetNextPoint(NavSys, PawnPosition, PlayerLocation);
	MyController->MoveToLocation(NextLocation, 20.f);

	bIsMoving = true;
}

FVector UAIRunComponent::GetNextPoint(const UNavigationSystemV1* NavSys, const FVector CharLoc, const FVector PlayerLoc)
{
	FNavLocation NavLocation;
	for(int32 i = 0; i < 100; ++i)
	{
		const auto Found = NavSys->GetRandomReachablePointInRadius(CharLoc, RunDistance, NavLocation);
		if (Found)
		{
			if ((PlayerLoc - NavLocation.Location).Size() >= MinDistanceToPlayer)
			{
				const auto v1 = PlayerLoc - CharLoc;
				const auto v2 = NavLocation.Location - CharLoc;
				const auto v3 = FMath::Abs(FMath::FindDeltaAngle(v2.Rotation().Yaw, v1.Rotation().Yaw));
					
				if (v3 < 90 || v3 > 270 ) continue;
				return NavLocation.Location;
			}
		}
	}
	return NavLocation.Location;
}

void UAIRunComponent::CheckPawn()
{
	if (MyPawn) return;
	if (!MyController) return;
	MyPawn = MyController->GetCharacter(); 
}
