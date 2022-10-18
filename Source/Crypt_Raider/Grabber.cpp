// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// UWorld* World = GetWorld();				//World->의 의미는 GetWorld()로 얻어진 UWorld의 주소값에 접근해서 UWorld에서 사용할 수 있는 어떠한 함수를 사용하겠다는 의미이다.
	// float Time = World->TimeSeconds;

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabberDist;
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
}

