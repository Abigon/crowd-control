// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrowdGameMode.generated.h"


UCLASS()
class CROWD_API ACrowdGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crowd AI")
	TArray<TSubclassOf<ACharacter>> BotsClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Crowd AI")
	int32 BotsAmount = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Crowd AI")
	int32 BotsInRow = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Crowd AI")
	FVector StartLoc = {0.f, -2000.f, 200.f};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Crowd AI")
	float StepX = 200.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Crowd AI")
	float StepY = 200.f;
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Crowd AI")
	void SpawnBotsByIndex(const int32 Index);

private:
	void SpawnBotsByClass(TSubclassOf<ACharacter> BotClass);
	void DestroyBots();
};
