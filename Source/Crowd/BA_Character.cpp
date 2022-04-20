// Fill out your copyright notice in the Description page of Project Settings.


#include "BA_Character.h"
#include "SkeletalMeshComponentBudgeted.h"


ABA_Character::ABA_Character(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<USkeletalMeshComponentBudgeted>(ACharacter::MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

}

