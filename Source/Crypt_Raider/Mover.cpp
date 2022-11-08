// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TartgetLocation = OriginalLocation;
	if(ShouldMove){				//Trigger에 해당하는 Tag를 가진 Actor가 있으면 움직이게 된다.
		TartgetLocation = OriginalLocation + MoveOffset;
	}

	FVector CurrnetLocation = GetOwner()->GetActorLocation();		//다 올라갔다면 다 올라간 위치가 현재 위치로 들어가겠지
	float Speed = MoveOffset.Length() / MoveTime;

	GetOwner()-> SetActorLocation(FMath::VInterpConstantTo(CurrnetLocation, TartgetLocation, DeltaTime, Speed));		//SetActorLocation에 FVector형을 넣어줘야 됌.

}

void UMover::SetShouldMove(bool NewShouldMove){
	ShouldMove = NewShouldMove;
}

/*포인터 설명*/
	// AActor* Owner = GetOwner();							//Actor(문)이 있는 주소를 Owner에 넣는다.
	// FString Name = (*Owner).GetActorNameOrLabel();		//(*Owner)를 통해 Actor에 접근을 해서 사용할 수 있는 함수를 사용한다. 현재 Actor의 이름을 넣는다.
	// //위와 동일한 코드: FString Name = Owner->GetActorNameOrLabel();
	
	// FVector MyLocation = Owner->GetActorLocation();		//Owner가 가르키는 주소의 값(Actor)을 들고와서 GetActorLocation함수를 실행시킨다. 그러면 이 스크립트가 들어있는 Actor의 Location(FVector)값이 MyLocation으로 들어간다.
	// FString MyLocationString = MyLocation.ToCompactString();

	// // float MyFloat = 5;
	// // float* YourFloat = &MyFloat;						//YourFloat에 MyFloat의 주소를 넣음 -> MyFloat와 YourFloat는 같은 주소를 가르킨다.
	// // 													//다른점은 YourFloat는 주소라서 값을 출력할 순 없다. -> UE_LOG(...TEXT("%f"), YourFloat)하면 주소가 출력된다.
	// // float FloatValue = *YourFloat;					//*YourFlaot의 뜻은 YourFloat 주소에 있는 값을 들고오라는 것이다. 즉 FloatValue 5가 들어온다.

	// UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s"), *Name);		//여기서 Name앞에 *이 붙는 이유: FString에서 * operator는 character array의 첫번째 주소를 담고 있다.
	// 																//그렇기 때문에 *Name은 이름을 담은 char array의 첫번째 주소를 나타내고 C와 동일하게 null character를 만날때까지 char를 출력한다.
	// 																//이와 같은 방식으로 FString을 출력한다.
	// UE_LOG(LogTemp, Display, TEXT("Location x: %f, y: %f, z: %f"), MyLocation.X, MyLocation.Y, MyLocation.Z);		

