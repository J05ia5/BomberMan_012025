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

    // Componente de malla estática para el bloque
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Malla")
    UStaticMeshComponent* MallaBomba;

protected:
    // Llamado cuando el juego inicia o el actor se genera
    virtual void BeginPlay() override;

    // Temporizador para controlar la destrucción
    FTimerHandle DestructionTimer;

    // Función que se ejecutará cuando finalice el temporizador
    void DestruirBomba();

    // Tiempo antes de destruirse (configurable desde el editor)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuración")
    float TiempoParaDestruir = 1.0f; // Tiempo en segundos

public:

    // Función para manejar colisiones o lógica especial (opcional) para graveedad e interaiones con objetos 
    UFUNCTION()
    // Configurar la función de colisión y destruccion
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

public:
    // Llamado cada frame
    virtual void Tick(float DeltaTime) override;
};
