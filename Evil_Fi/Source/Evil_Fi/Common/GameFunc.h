#pragma once

#include "CoreMinimal.h"
// �������� ���Ǵ� �Լ��Դϴ�.

// LoadObject ���� �Լ��Դϴ�. [9/8/2019 ImTaeJun]
template <typename T>
static T* LoadObject(FString strPath)
{
	return LoadObject<T>(nullptr, strPath, nullptr, LOAD_None, nullptr);
}