#pragma once

// ���ҽ����� �ε��ϰ� ĳ���ϴ� �������Դϴ� [9/11/2019 ImTaeJun]

#include "DesignPattern/Singleton.h"
#include "Common/GameType.h"

#include <Engine/World.h>
#include "UnrealString.h"

class ResourceManager : public TSingleton<ResourceManager>
{
public:
	template <typename T>
	T*		LoadResource(const FString& strPath);
	void	UnLoadResources();

private:
	TMap<FString, TWeakObjectPtr<UObject>>	m_mapResources;
};

template <typename T>
T* ResourceManager::LoadResource(const FString& strPath)
{
	T* pResourceObj = nullptr;

	if (m_mapResources.Contains(strPath) == true)
	{
		TWeakObjectPtr<UObject>& wpObject = m_mapResources[strPath];
		if (wpObject.IsValid() == false)
		{
			pResourceObj = LoadObject<T>(nullptr, strPath);
			if (pResourceObj == nullptr)
				return nullptr;

			pResourceObj->AddToRoot();
			wpObject = MakeWeakObjectPtr(pResourceObj);
		}
		else
			pResourceObj = wpObject.Get();
	}
	else
	{
		T* pResourceObj = LoadObject<T>(nullptr, strPath);
		if (pResourceObj == nullptr)
			return nullptr;

		pResourceObj->AddToRoot();
		m_mapResources.Add(strPath, MakeWeakObjectPtr(pResourceObj));
	}
	return pResourceObj;
}
