#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "ShootCounter.h"
#include "RepsiPlayerController.h"
#include "RepsiPawn.generated.h"

UCLASS()
class ARepsiPawn : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ARepsiPlayerController* FPA;

	/** Scene component indicating where the pawn's Weapon should be attached. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USceneComponent* WeaponHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UShootCounter* CounterHud;

	/** The weapon that this player is holding, if any. */
	UPROPERTY(ReplicatedUsing=OnRep_Weapon, Transient, VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	class AWeapon* Weapon;

	/** How far into the scene we'll trace in order to figure out what the player is aiming at with their weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float AimTraceDistance;
	/** Material instance assigned to the character mesh, giving us control over the shader parameters at runtime. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	class UMaterialInstanceDynamic* MeshMID;

	/** An arbitrary color that identifies this player; assigned by the game mode on spawn. Controls the color of the mesh. */
	UPROPERTY(ReplicatedUsing=OnRep_Color, Transient, BlueprintReadOnly, Category="Player")
	FLinearColor Color;



	// Expose widget class to Blueprint or Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UShootCounter* WidgetComponent;

	ARepsiPawn(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	/** Server-only: updates the color applied to this pawn's mesh MID. */
	void AuthSetColor(const FLinearColor& InColor);

	// Custom cast function template
	template <typename ToType, typename FromType>
	ToType* SafeCast(FromType* Object)
	{
		if (ToType* CastedObject = Cast<ToType>(Object))
		{
			// Cast succeeded, return the casted object
			return CastedObject;
		}
		else if (Object)
		{
			// Cast failed, print the class name of the original object
			FString ObjectClassName = Object->GetClass()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast object of class %s to %s"), *ObjectClassName, *ToType::StaticClass()->GetName());

			// Optional: Display message on screen
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to cast from %s to %s"), *ObjectClassName, *ToType::StaticClass()->GetName()));
			}
		}
		else
		{
			// Object is null, handle null object case
			UE_LOG(LogTemp, Warning, TEXT("Object is nullptr, cannot cast to %s"), *ToType::StaticClass()->GetName());

			// Optional: Display message on screen
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Object is nullptr, cannot cast to %s"), *ToType::StaticClass()->GetName()));
			}
		}

		// Return nullptr since the cast failed
		return nullptr;
	}

private:
	/** For client-side Pawns, ensures that the Weapon is attached to the WeaponHandle. */
	UFUNCTION()
	void OnRep_Weapon();

	/** Updates the MeshMID's color parameter to match our current Color property. */
	UFUNCTION()
	void OnRep_Color();


	UFUNCTION() void OnFire();
	UFUNCTION() void OnMoveForward(float AxisValue);
	UFUNCTION() void OnMoveRight(float AxisValue);
	UFUNCTION() void OnMoveUp(float AxisValue);
	UFUNCTION() void OnLookRight(float AxisValue);
	UFUNCTION() void OnLookUp(float AxisValue);
	UFUNCTION() void OnLookRightRate(float AxisValue);
	UFUNCTION() void OnLookUpRate(float AxisValue);


};
