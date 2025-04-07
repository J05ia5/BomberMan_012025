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


	// Componente de malla estática para el bloque
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

	// Función para mover al enemigo
public:
	// Lógica de movimiento aleatorio
	FVector MovimientoActual;
	float DistanciaRecorrida;
	const float DistanciaMaxima = 500.0f;

private:
	// Función para cambiar la dirección del movimiento
	void CambiarDireccion();

	// Función para mover al enemigo
	bool DetectarObstaculo(FVector Destino);
};
