// Proje ayarlarının açıklama sayfasındaki telif hakkı notlarını doldurun.

#pragma once // Dosyanın birden fazla kez eklenmesini önler.

#include "CoreMinimal.h" // Unreal Engine temel sınıf ve işlevlerini içerir.
#include "GameFramework/Actor.h" // AActor sınıfını kullanmak için gerekli.
#include "MovingPlatform.generated.h" // Unreal Engine'in yansıtma sistemi için gereklidir.

UCLASS()
// AMovingPlatform sınıfı, bir hareket eden platformu temsil eder ve AActor sınıfından türetilmiştir.
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:	
	// Bu aktörün varsayılan değerlerini ayarlar.
	AMovingPlatform();

protected:
	// Oyun başladığında veya aktör oluşturulduğunda çağrılır.
	virtual void BeginPlay() override;

public:	
	// Her karede çağrılır.
	virtual void Tick(float DeltaTime) override;

private:
	// Platformun hareket hızını belirten bir vektör.
	UPROPERTY(EditAnywhere, Category="Moving")
	FVector PlatformVelocity = FVector(100,0,0);

	// Platformun taşınması gereken maksimum mesafeyi tanımlar.
	UPROPERTY(EditAnywhere, Category="Moving")
	float MovedDistance = 100;

	// Platformun döndürme hızını belirten bir rotator.
	UPROPERTY(EditAnywhere, Category="Rotation")
	FRotator RotationVelocity;

	// Platformun başlangıç konumunu saklar.
	FVector StartLocation;

	// Platformun hareketini gerçekleştiren özel bir işlev.
	void MovePlatform(float DeltaTime);	
	
	// Platformun rotasyonunu gerçekleştiren özel bir işlev.
	void RotatePlatform(float DeltaTime);

	// Platformun başlangıç konumuna geri dönmesi gerekip gerekmediğini kontrol eder.
	bool ShouldPlatformReturn() const;

	// Platformun başlangıç konumundan ne kadar uzaklaştığını hesaplar.
	float GetDistanceMoved() const;
};
