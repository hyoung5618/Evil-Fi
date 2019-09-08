#pragma once

#include "CoreMinimal.h"
// 공용으로 사용되는 함수입니다.

// LoadObject 랩핑 함수입니다. [9/8/2019 ImTaeJun]
template <typename T>
static T* LoadObject(FString strPath)
{
	return LoadObject<T>(nullptr, strPath, nullptr, LOAD_None, nullptr);
}