// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CasingBase.generated.h"

UCLASS(Abstract)
class PROJECTZ_API ACasingBase : public AActor
{
	GENERATED_BODY()

public:
	ACasingBase();

	/**Let the casing know that it has been spawned.
		* If this function isn't called when spawning a casing, it will not get deleted properly.
		*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Projz | Casing")
	void OnSpawn();

	/**Adds an impulse to this casing.
	 * This function is usually called to launch the casing in a specific direction.
	 */
	UFUNCTION(BlueprintCallable, Category = "Projz | Casing")
	void ApplyImpulse(FVector Direction, const FVector Strength);

	/**Returns the value of bUpdateScale.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projz | Casing")
	bool ShouldUpdateScale() const { return bUpdateScale; }

	/**Returns the value of DestroyDelay.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projz | Casing")
	float GetDestroyDelay() const { return DestroyDelay; }

protected:
	/*Pivot.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz")
		USceneComponent* Pivot;

	/**Casing mesh.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz")
	class UProjectileMovementComponent* ProjectileMovement;


	void BeginPlay() override;

private:
	/**Should we scale the casing down as time goes on?
	* This is very useful for casings that don't need to be visible after the first few moments, but do need all
	* other behavior.
	*/
	UPROPERTY(EditAnywhere, Category = "Projz | Casing")
		bool bUpdateScale = true;

	/**Speed of rotation for this casing.*/
	UPROPERTY(EditAnywhere, Category = "Projz | Casing")
		float RotationSpeed = 2500.0f;

	/**Range of possible delay values used to destroy the casing.
	 * In short, a random value between these two will be the time it takes for the casing to be destroyed.
	 */
	UPROPERTY(EditAnywhere, Category = "Projz | Casing")
		FVector2D DestroyDelayRange = FVector2D(0.5f, 1.0f);

	/**Sound played when the casing is destroyed!
	 * We could have used a surface data for this, but we don't have enough sounds yet.
	 */
	UPROPERTY(EditAnywhere, Category = "Projz | Casing")
		USoundBase* Sound;

	/**Amount of time required to pass before destroying this object. Works like object life time.*/
	float DestroyDelay = 1.0f;

	/**Start Implementation.*/
	void OnSpawn_Implementation();
	void ApplyImpulse_Implementation(FVector Direction, const FVector Strength) const;
	/**End Implementation.*/

	/**Tick.*/
	virtual void Tick(float DeltaTime) override;
};
