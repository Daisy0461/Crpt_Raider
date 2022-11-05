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

	for(int32 i=0; i<Actors.Num(); i++){
		FString name = Actors[i]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Actor's name: %s"), *name);
	}

	// //위의 for문을 다음과 같이 사용이 가능하다.
	// for(AActor* Actor : Actors){		//우리가 Pointer나 변수들을 넣은 Array를 루프 돌릴 때 사용한다. Actors에 있는 모든 요소를 다 방문하며 TArray뿐만 아니라 다른 변수를 담는 타입들도 사용이 가능하다.
	// 	FString name = Actor->GetActorNameOrLabel();				//위 for에서 사용한 Actor[i] 대신에 Actor를 사용한다. 순차적으로 방문하기 때문에 i가 사라지는 것이다.
	// 	UE_LOG(LogTemp, Display, TEXT("Actor's name: %s"), *name);
	// }

}