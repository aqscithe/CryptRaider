// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component)
		{
			Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
		}

		FString Name = Actor->GetActorLabel();
		Door->SetShouldMoveBool(true);
	}
	else
	{
		Door->SetShouldMoveBool(false);
	}


}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);


	if (Actors.Num() > 0)
	{
		for (auto Actor : Actors)
		{
			bool HasUnlockTag = Actor->ActorHasTag(UnlockTag);
			bool IsGrabbed = Actor->Tags.Contains("Grabbed");
			if (HasUnlockTag  && !IsGrabbed)
			{
				return Actor;
			}
		}
	}
	return nullptr;
}

void UTriggerComponent::SetOpenDoor(UOpenDoor* NewDoor) 
{
	Door = NewDoor;
}