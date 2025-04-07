// your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomba.generated.h"

UCLASS()
class BOMBERMAN_012025_API ABomba : public AActor
{
    GENERATED_BODY()

public:
    // Constructor: Sets default values for this actor's properties
    ABomba();

    // Componente de malla est�tica para el bloque
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Malla")
    UStaticMeshComponent* MallaBomba;

protected:
    // Llamado cuando el juego inicia o el actor se genera
    virtual void BeginPlay() override;

    // Temporizador para controlar la destrucci�n
    FTimerHandle DestructionTimer;

    // Funci�n que se ejecutar� cuando finalice el temporizador
    void DestruirBomba();

    // Tiempo antes de destruirse (configurable desde el editor)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuraci�n")
    float TiempoParaDestruir = 5.0f; // Tiempo en segundos

public:

    // Funci�n para manejar colisiones o l�gica especial (opcional) para graveedad e interaiones con objetos 
    UFUNCTION()
    // Configurar la funci�n de colisi�n y destruccion
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

public:
    // Llamado cada frame
    virtual void Tick(float DeltaTime) override;
};
