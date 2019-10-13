#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"

#include "DT_Item.generated.h"

// �ӽ� ������ @ĳ���� �ɷ�ġ
UENUM(BlueprintType)
enum class ECharStatType : uint8
{
	NONE,

	// ü��
	HP			UMETA(DisplayName = "HP"),

	// �ִ� ü��
	HP_MAX		UMETA(DisplayName = "Max HP"),

	// ���ݷ�
	ATTACK		UMETA(DisplayName = "Attack"),

	// ����
	DEFENCE		UMETA(DisplayName = "Defence"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE, 

	// ����
	POTION UMETA(DisplayName = "Potion"),
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	EItemType		ItemType;

	// Ÿ�� �ɷ�ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	ECharStatType	TargetStatType;

	// ������ �ɷ�ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32			Value;
};

USTRUCT(BlueprintType)
struct FItemTextData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FName	ItemName;

	// ������ ����
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
	// ������ ������ ���̺�
	class UDataTable* m_pItemDataTable;

	// ������ �ؽ�Ʈ ���̺�
	class UDataTable* m_pItemTextTable;
};
