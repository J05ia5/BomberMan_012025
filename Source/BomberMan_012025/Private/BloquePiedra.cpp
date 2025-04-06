// Fill out your copyright notice in the Description page of Project Settings.


#include "BloquePiedra.h"

ABloquePiedra::ABloquePiedra()
{
	if(MallaBloque)
	{
		// Asignar un material espec�fico para el bloque de piedra
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_CobbleStone_Pebble.M_CobbleStone_Pebble'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}
}

void ABloquePiedra::BeginPlay()
{
	Super::BeginPlay();
	// Aqu� puedes agregar cualquier l�gica adicional que necesites al inicio del juego
}

