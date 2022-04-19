// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "RunAIController.generated.h"


UCLASS()
class CROWD_API ARunAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float MinDistanceToTarget = 200.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float MinDistanceToPlayer = 600.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float RunDistance = 3000.f;

private:
	UPROPERTY()
	ACharacter* PlayerChar = nullptr;
	UPROPERTY()
	ACharacter* Char = nullptr;

	bool bIsMoving = false;
	FVector NextLocation;

public:
	virtual void Tick(float DeltaSeconds) override;

	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void CheckPlayer();
	void CheckCharPosition();

	FVector GetNextPoint(const class UNavigationSystemV1* NavSys, const FVector CharLoc, const FVector PlayerLoc);
	
	ACharacter* GetPlayerChar();

	
};
