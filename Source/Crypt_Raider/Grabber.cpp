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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	UPhysicsHandleComponent* PhysicsHandle = PullOutGetPhysicsHandle();
	if(PhysicsHandle == nullptr){
		return;
	}

	if(PhysicsHandle->GetGrabbedComponent() != nullptr){			//무언가를 쥐고 있다면 아래를 실행 
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

	// UWorld* World = GetWorld();				//World->의 의미는 GetWorld()로 얻어진 UWorld의 주소값에 접근해서 UWorld에서 사용할 수 있는 어떠한 함수를 사용하겠다는 의미이다.
	// float Time = World->TimeSeconds;

	// float Damage;
	// float& DamageRef = 	Damage;			//&의 의미는 float의 Reference라는 의미이다. float가 아니다. pointer memory를 할당한다. Damage의 Reference가 DamageRef에 들어간다. (Reference도 주소값이 들어간다.)
	// if(HasDamage(Damage)){				//이 함수처럼 Damage변수가 방금 전에 선언되었고 초기화되지 않은 상태에서 바로 함수에 넘긴다면 그것은 Out 파라미터일 것이다. -> Out 파라미터는 값는 해당 파라미터의 값을 지정해준다는 것이다.
	// 	PrintDamage(Damage);
	// }

	// //UE_LOG(LogTemp, Display, TEXT("DamageRef: %f   //  Damage: %f"), DamageRef, Damage);	//다음과 같이 ulog를 출력해도 주소값이 나오는것이 아니라 Damage에 할당되어있는 값이 출력된다.
	// 																						//Reference는 변수의 다름 이름을 붙여주는 것과 같다! 닉네임이라고 생각하면 될거같다.
	// PrintDamage(Damage);		//이와 같이 코딩하면 파라미터가 float&(Reference)이기 때문에 PrintDamage 함수 안에서 Damage라는 변수를 Copy해서 사용하지 않고 Tick함수에 선언된 Damage의 주소를 들고와서 PrintDamage에 넘긴다.
	// 							//이렇게 되면 Tick에 있는 Damage에 접근을 하고 값을 쉽게 바꿀 수 있으며 Copy하지 않으니 메모리 절약도 된다.
}

void UGrabber::PrintDamage(const float& Damage){				//파라미터에 const float& Damage가 들어가면 이 Reference는 교체될 수 없다는 의미이다. 즉, 바로 아래 코드는 실행이 되지 않는다. 	당연하게도 const가 붙어있지 않은 함수도 사용 불가능하다.
	//Damage = 10;												//Tick의 주소값이 파라미터로 들어오고 Damage는 해당 주소에 있는 변수 값을 의미하기 때문에 여기서 Damage를 바꾸면 Tick에 있는 Damage도 바뀐다.
	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Damage);		//여기서도 Tick에 있는 Damage의 주소값이 들어오기 때문에 여기 있는 Damage와 Tick의 Damage는 동일한 값을 가진다.
}

bool UGrabber::HasDamage(float& OutDamage){						//이와 같이 Reference가 파라미터로 들어가있지만 const가 붙어있지 않다면 이것은 Out 파라미터일 확률이 높다. 특히 Out이 앞에 붙어있다면 무조건이다.
	OutDamage = 5;
	return true;
}

void UGrabber::Release(){
	UPhysicsHandleComponent* PhysicsHandle = PullOutGetPhysicsHandle();
	if(PhysicsHandle == nullptr){
		return;
	}

	if(PhysicsHandle->GetGrabbedComponent() != nullptr){		//무언가를 쥐고 있다면
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();			//이것을 실행시키는 이유가 Grab을 실행시키고 움직이지 않으면 Physic 최적화를 위해 Rigid가 꺼질 수 있으므로 놓을 때 다시 켜줘야한다. 다시 켜지 않으면 물리가 적용되지 않아서 놓을 수 없을 수도 있다.
		PhysicsHandle->ReleaseComponent();
	}

}

void UGrabber::Grab(){
	UPhysicsHandleComponent* PhysicsHandle = PullOutGetPhysicsHandle();
	if(PhysicsHandle == nullptr){
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if(HasHit){
		isGrabbed = true;
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent, 
			NAME_None, 
			HitResult.ImpactPoint, 
			//HitResult.GetComponent()->GetComponentRotation()
			GetComponentRotation()
			);
	}

}

UPhysicsHandleComponent* UGrabber::PullOutGetPhysicsHandle() const{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr){
		UE_LOG(LogTemp, Warning, TEXT("Grabber reauires a UPhysicsHandleComponent."));
	}
	return PhysicsHandle;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutResult) const{		//Out 파라미터 제대로 이해하고 사용하기 -> 정리하기/
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabberDist;
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
	//DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Red, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(OutResult, Start, End, 
	FQuat::Identity, ECC_GameTraceChannel2, Sphere
	);		//5번째 파라미터인 ECollisionChannel 찾는 방법: 프로젝트 파일->Config->DefalutEngine.ini를 VSCode로 열기->Grabber서치 후 Channel=~~이다.

}
 