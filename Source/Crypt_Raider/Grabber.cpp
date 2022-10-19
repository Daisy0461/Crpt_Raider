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

	float Damage = 0; float plus = 5;
	float& DamageRef = 	Damage;			//&의 의미는 float의 Reference라는 의미이다. float가 아니다. pointer memory를 할당한다. Damage의 Reference가 DamageRef에 들어간다. (Reference도 주소값이 들어간다.)
	DamageRef = plus;
	UE_LOG(LogTemp, Display, TEXT("DamageRef: %f   //  Damage: %f"), DamageRef, Damage);	//다음과 같이 ulog를 출력해도 주소값이 나오는것이 아니라 Damage에 할당되어있는 값이 출력된다.
																							//Reference는 변수의 다름 이름을 붙여주는 것과 같다! 닉네임이라고 생각하면 될거같다.
	
}

