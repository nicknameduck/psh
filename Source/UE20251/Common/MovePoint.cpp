// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePoint.h"

// Sets default values
AMovePoint::AMovePoint()
{
	PrimaryActorTick.bCanEverTick = false;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void AMovePoint::BeginPlay()
{
	Super::BeginPlay();
	
}
