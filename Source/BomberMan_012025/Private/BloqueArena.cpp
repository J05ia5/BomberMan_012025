// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueArena.h"

ABloqueArena::ABloqueArena()
{
	if (MallaBloque)
	{
		// Asignar un material espec�fico para el bloque de arena
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/Arena2k.Arena2k'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}
}

void ABloqueArena::BeginPlay()
{
	Super::BeginPlay();
	// Aqu� puedes agregar cualquier l�gica adicional que necesites al inicio del juego
}
