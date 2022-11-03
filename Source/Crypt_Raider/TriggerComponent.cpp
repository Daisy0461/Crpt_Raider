// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()													//라이브 코딩에 바로 적용되지 않아서 에디터를 닫고 빌드를 한 후 에디터를 다시 열어야한다.
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);		//Super이기 때문에 Parent의 Tick을 부른다. Parent는 h파일에서 확인할 수 있고 여기선 UBoxComponent이다.

	TArray<AActor*> Actors;				//Actor*를 담는 Array 생성 Vector처럼 크기가 정해져있지 않은 Array이다.
	GetOverlappingActors(Actors);		//Tick에 따라 여러 개의 Actor가 Overlapping 될 수 있기 때문에 TArray를 받는거 같음

	if(Actors.Num() > 0){
		FString name = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Actor[0]'s name: %s"), *name);
	}

}