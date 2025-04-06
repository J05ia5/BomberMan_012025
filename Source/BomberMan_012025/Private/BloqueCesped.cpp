// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueCesped.h"

ABloqueCesped::ABloqueCesped()
{
	if (MallaBloque)
	{
		// Asignar un material espec�fico para el bloque de c�sped
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}
}

void ABloqueCesped::BeginPlay()
{
	Super::BeginPlay();
	// Aqu� puedes agregar cualquier l�gica adicional que necesites al inicio del juego
}
