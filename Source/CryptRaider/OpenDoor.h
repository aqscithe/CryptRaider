// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMoveBool(bool ToggleShouldMove);

private:

	//UPROPERTY(EditAnywhere)
	//FRotator AngleDegreeOffset;
	//
	//UPROPERTY(EditAnywhere)
	//float OpenTime = 4;
	//
	//FRotator OriginalRotation;

	UFUNCTION(BlueprintCallable)
	void SetDoorMesh(UStaticMeshComponent* NewDoorMesh);

	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 3;

	UStaticMeshComponent* DoorMesh;

	bool ShouldMove = false;

	FVector OriginalLocation;
	

		
};
