// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

UCLASS()
class BOMBERMAN_012025_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo();


	// Componente de malla est�tica para el bloque
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Malla")
	UStaticMeshComponent* MallaEnemigo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Funci�n para mover al enemigo
public:
	// L�gica de movimiento aleatorio
	FVector MovimientoActual;
	float DistanciaRecorrida;
	const float DistanciaMaxima = 500.0f;

private:
	// Funci�n para cambiar la direcci�n del movimiento
	void CambiarDireccion();

	// Funci�n para mover al enemigo
	bool DetectarObstaculo(FVector Destino);
};
