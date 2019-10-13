#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"

#include "DT_Item.generated.h"

// 임시 데이터 @캐릭터 능력치
UENUM(BlueprintType)
enum class ECharStatType : uint8
{
	NONE,

	// 체력
	HP			UMETA(DisplayName = "HP"),

	// 최대 체력
	HP_MAX		UMETA(DisplayName = "Max HP"),

	// 공격력
	ATTACK		UMETA(DisplayName = "Attack"),

	// 방어력
	DEFENCE		UMETA(DisplayName = "Defence"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE, 

	// 포션
	POTION UMETA(DisplayName = "Potion"),
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	EItemType		ItemType;

	// 타겟 능력치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	ECharStatType	TargetStatType;

	// 아이템 능력치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32			Value;
};

USTRUCT(BlueprintType)
struct FItemTextData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FName	ItemName;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FName	ItemDesc;
};

UCLASS()
class UDT_Item : public UObject
{
	GENERATED_BODY()

public:
	UDT_Item();

public:
	FItemData* GetItemData(int32 nItemUnique);
	FItemTextData* GetItemTextData(int32 nItemUnique);

public: // ItemDataTable
	int32 GetItemValue(int32 nItemUnique);

public: // ItemTextTable
	FName GetItemName(int32 nItemUnique);
	FName GetItemDesc(int32 nItemUnique);

private:
	// 아이템 데이터 테이블
	class UDataTable* m_pItemDataTable;

	// 아이템 텍스트 테이블
	class UDataTable* m_pItemTextTable;
};
