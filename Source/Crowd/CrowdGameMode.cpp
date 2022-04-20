// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowdGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ACrowdGameMode::SpawnBotsByIndex(const int32 Index)
{
	DestroyBots();
	if (BotsClasses.IsValidIndex(Index))
	{
		SpawnBotsByClass(BotsClasses[Index]);
	}
}

void ACrowdGameMode::SpawnBotsByClass(TSubclassOf<ACharacter> BotClass)
{
	if (!GetWorld() || !BotClass) return;
	
	const FRotator SpawnRot = FRotator(0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLoc = StartLoc;
	int32 Pos = 0;
	int32 Row = 0;
	for (int32 i = 0; i < BotsAmount; ++i)
	{
		SpawnLoc.X = StartLoc.X + Row * StepX;
		SpawnLoc.Y = StartLoc.Y + Pos * StepY;
		auto Bot = GetWorld()->SpawnActor<ACharacter>(BotClass, SpawnLoc, SpawnRot, SpawnParams);

		++Pos;
		if (Pos >= BotsInRow)
		{
			Pos = 0; ++Row;
		}
	}

}

void ACrowdGameMode::DestroyBots()
{
	//if (!GetWorld()) return;

	TArray<AActor*> ResultActors;
	UGameplayStatics::GetAllActorsOfClass(this, ACharacter::StaticClass(), ResultActors);

	const auto Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	for (const auto Actor : ResultActors)
	{
		if (Actor != Player)
		{
			Actor->Destroy();
		}
	}
}
