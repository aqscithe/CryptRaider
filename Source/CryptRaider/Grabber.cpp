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

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	
	

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Physics Handle - nullptr"));
	}
	return PhysicsHandle;
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult Hit;
	bool HasHit = GetGrabbableInReach(Hit);

	if (HasHit)
	{
		AActor* Actor = Hit.GetActor();
		UPrimitiveComponent* HitComponent = Hit.GetComponent();

		TArray<FName>& HitActorTags = Actor->Tags;
		UE_LOG(LogTemp, Display, TEXT("Number of tags on grabbed actor: %d"), HitActorTags.Num());

		if (!HitActorTags.Contains("Grabbed"))
		{
			HitComponent->WakeAllRigidBodies();
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitComponent,
				NAME_None,
				Hit.ImpactPoint,
				GetComponentRotation()
			);
			HitActorTags.Add("Grabbed");
			UE_LOG(LogTemp, Display, TEXT("Number of tags POST GRAB: %d"), HitActorTags.Num());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s already Grabbed"), *Actor->GetActorLabel());
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("NO HIT"));
	}


	
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHit) const
{
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * MaxGrabDist;

	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Cyan);
	DrawDebugSphere(GetWorld(), LineEnd, 10, 20, FColor::Green, false, 5.0F);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(
		OutHit,
		LineStart,
		LineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
		
	}
	else 
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing Released"));
	}
}

