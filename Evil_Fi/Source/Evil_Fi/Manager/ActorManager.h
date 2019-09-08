#include "DesignPattern/Singleton.h"
#include "Common/GameType.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>

class ActorManager : public TSingleton<ActorManager>
{
public:

	template<typename T>
	T* CreateActor(UWorld* pWorld, FName strName, const FVector& Location = FVector(0.f, 0.f, 0.f), const FRotator& Rotation = FRotator(0.f, 0.f, 0.f))
	{
		if (pWorld == nullptr)
			return nullptr;

		FActorSpawnParameters SPAWNPARAMETER;
		SPAWNPARAMETER.Name = strName;
		T* pActor = pWorld->SpawnActor<T>(Location, Rotation, SPAWNPARAMETER);

		if (pActor) {
			TArray<TSharedPtr<AActor>>* pArrActor = m_mapActorArry.Find(strName);
			if (pArrActor == nullptr)
			{
				TArray<TSharedPtr<AActor>> arrActor;
				arrActor.Add(MakeShareable<AActor>(pActor));
				m_mapActorArry.Emplace(strName, arrActor);
			}
			else
			{
				pArrActor->Add(MakeShareable<AActor>(pActor));
			}
			return pActor;
		}

		return nullptr;
	}

	void DeleteActor()
	{

	}

	void FindActor()
	{

	}

	void LoopActor()
	{

	}

private:
	TMap<FName, TArray<TSharedPtr<AActor>>> m_mapActorArry;
};