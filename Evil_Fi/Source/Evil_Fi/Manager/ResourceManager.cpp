#include "ResourceManager.h"

void ResourceManager::UnLoadResources()
{
	for (auto resIter = m_mapResources.CreateIterator(); resIter; ++resIter)
	{
		if (resIter.Value().IsValid() == true)
			resIter.Value()->RemoveFromRoot();
	}
	m_mapResources.Empty();
}

