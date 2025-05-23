// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueBurbuja.h"

ABloqueBurbuja::ABloqueBurbuja()
{
	if (MallaBloque)
	{
		PosicionInicial = FVector::ZeroVector; // Inicializar PosicionInicial
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/Burbuja.Burbuja'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}

	}
	bPuedeMoverse = true;//FMath::RandBool(); // activa o desactiva el movimiento

}
void ABloqueBurbuja::BeginPlay()
{
	Super::BeginPlay();
	// Aqu� puedes agregar cualquier l�gica adicional que necesites al inicio del juego

	// Aqu� puedes agregar cualquier l�gica adicional que necesites al inicio del juego
	PosicionInicial = GetActorLocation(); // Asignar la posici�n inicial al comenzar el juego
}
void ABloqueBurbuja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Aqu� puedes agregar cualquier l�gica adicional que necesites en cada tick
	// Por ejemplo, puedes mover el bloque o aplicar efectos visuales
	if (bPuedeMoverse)
	{
		float NuevaAltura = PosicionInicial.Z + FMath::Sin(GetWorld()->GetTimeSeconds() * 2.0f) * 100.0f;
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, NuevaAltura));
	}
}
