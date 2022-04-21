// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIRunComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROWD_API UAIRunComponent : public UActorComponent
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
	ACharacter* MyPawn = nullptr;
	UPROPERTY()
	class AAIController* MyController = nullptr;

	bool bIsMoving = false;
	FVector NextLocation;

	
public:
	UAIRunComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool IsMoving() const { return bIsMoving; }

protected:
	virtual void BeginPlay() override;


private:
	void CheckPlayer();
	void CheckCharPosition();

	FVector GetNextPoint(const class UNavigationSystemV1* NavSys, const FVector CharLoc, const FVector PlayerLoc);

	void CheckPawn();

};
