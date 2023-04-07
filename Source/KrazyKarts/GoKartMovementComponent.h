// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"


USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;

	inline bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetVelocity(const FVector& NewVelocity);
	FVector GetVelocity() const;
	void SetThrottle(const float& NewThrottle);
	void SetSteeringThrow(const float& NewSteeringThrow);

	void SimulateMove(const FGoKartMove& Move);

	inline FGoKartMove GetLastMove() const;

private:

	FGoKartMove CreateMove(const float& DeltaTime);

	void ApplyRotation(float DeltaTime, float SteeringThrowToApply);

	void UpdateLocationFromVelocity(const float& DeltaTime);

	inline FVector GetAirResistance();

	FVector GetRollingResistance();


	// The mass of the car(kg).
	UPROPERTY(EditAnywhere)
	float Mass;

	// The maximum force, when throttle is down(N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce;

	// The minimum radius of car turning cicle at full lock(m).
	UPROPERTY(EditAnywhere)
	float MinTurningRadius;

	// Higher means more drag(kg/m).
	UPROPERTY(EditAnywhere)
	float DragCoefficient;

	// Higher means more rolling resistance.
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient;

	FVector Velocity;
	
	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;
};
