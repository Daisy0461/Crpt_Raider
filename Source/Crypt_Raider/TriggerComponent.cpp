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

	if(Mover == nullptr){
		return;
	}

	AActor* Actor = GetAceptableActor();
	if(Actor != nullptr){																	//UPrimitiveComponent = USceneComponent이며 충돌 데이터로 렌더링되거나 사용되는 기하학를 생성하는 것이다.
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());		//Actor의 RootComponent의 USceneComponent가 UPrimitiveComponent인것이 맞다면 Output은 UPrimitive의 Pointer가 되고 아니면 nullptr이 출력된다.
		if(Component != nullptr){
			Component->SetSimulatePhysics(false);		//UPrimitive에 있는 함수인 SetSimulatePhysics이며 UPrimitiveComponent가 충돌을 계산하는데 여기서 Actor의 Physic를 끄겠다는 것이다.
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);		//찾은 Actor(가고일 동상)에 이 Component를 붙인다..?
		Mover->	SetShouldMove(true);
	}else{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover){			//SetMover로 Mover가 설정이 된다. 그럼 이게 어디서 사용되냐? -> BP에서 Begin할 때 Wall에 있는 Mover가 NewMover로 들어온다.
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAceptableActor() const
{
	TArray<AActor*> Actors;				//Actor*를 담는 Array 생성 Vector처럼 크기가 정해져있지 않은 Array이다.
	GetOverlappingActors(Actors);		//Tick에 따라 여러 개의 Actor가 Overlapping 될 수 있기 때문에 TArray를 받는거 같음

	for(AActor* Actor : Actors){
		bool HasAcceptableTag = Actor->ActorHasTag(tag);			
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");

		if(HasAcceptableTag && !IsGrabbed){
			return Actor;
		}
	}

	return nullptr;		// 이게 꼭 있어야한다.
}