// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (ShouldMove)
	//{
	//	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//
	//	FRotator TargetRotation = OriginalRotation + AngleDegreeOffset;
	//	float OpenSpeed = OriginalRotation.GetManhattanDistance(TargetRotation) / OpenTime;
	//
	//	FRotator NewRotation = (CurrentRotation + AngleDegreeOffset) * OpenSpeed * DeltaTime;
	//	GetOwner()->AddActorLocalRotation(NewRotation);
	//}
	


	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float MoveSpeed = FVector::Dist(OriginalLocation, TargetLocation) / MoveTime;
	
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		GetOwner()->SetActorLocation(NewLocation);
	}
	

}

void UOpenDoor::SetShouldMoveBool(bool ToggleShouldMove)
{
	ShouldMove = ToggleShouldMove;
}

void UOpenDoor::SetDoorMesh(UStaticMeshComponent* NewDoorMesh)
{
	DoorMesh = NewDoorMesh;
}

