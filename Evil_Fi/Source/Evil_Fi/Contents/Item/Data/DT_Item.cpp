#include "DT_Item.h"

#include "ConstructorHelpers.h"

#include "Common/CommonLog.h"

//////////////////////////////////////////////////////////////////////////
// AItemDataTables
UDT_Item::UDT_Item()
{
	// Item���� �����Ͱ� ���ǵ� ������ ���̺��� �о�ɴϴ�.

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataTable(TEXT("/Game/Data/ItemDataTable"));
	if (ItemDataTable.Succeeded())
	{
		m_pItemDataTable = ItemDataTable.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTextDataTable(TEXT("/Game/Data/ItemTextDataTable"));
	if (ItemTextDataTable.Succeeded())
	{
		m_pItemTextTable = ItemTextDataTable.Object;
	}
}

//////////////////////////////////////////////////////////////////////////
// ������ ������ ��ȯ
FItemData* UDT_Item::GetItemData(int32 nItemUnique)
{
	FItemData* pDataRow = m_pItemDataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(nItemUnique))), FString(""));
	if (nullptr == pDataRow)
	{
		UE_LOG(DataTableLog, Error, TEXT("Invalid Item Data - ItemUnique is %d"), nItemUnique);
		return nullptr;
	}

	return pDataRow;
}

//////////////////////////////////////////////////////////////////////////
// ������ �ؽ�Ʈ ������ ��ȯ
FItemTextData* UDT_Item::GetItemTextData(int32 nItemUnique)
{
	FItemTextData* pDataRow = m_pItemTextTable->FindRow<FItemTextData>(FName(*(FString::FormatAsNumber(nItemUnique))), FString(""));
	if (nullptr == pDataRow)
	{
		UE_LOG(DataTableLog, Error, TEXT("Invalid Item Text Data - ItemUnique is %d"), nItemUnique);
		return nullptr;
	}

	return pDataRow;
}

//////////////////////////////////////////////////////////////////////////
// ������ �� ��������
int32 UDT_Item::GetItemValue(int32 nItemUnique)
{
	FItemData* pDataRow = GetItemData(nItemUnique);
	if (nullptr == pDataRow)
	{
		return INDEX_NONE;
	}

	return pDataRow->Value;
}

//////////////////////////////////////////////////////////////////////////
// ������ �̸� ��������
FName UDT_Item::GetItemName(int32 nItemUnique)
{
	FItemTextData* pDataRow = GetItemTextData(nItemUnique);
	if (nullptr == pDataRow)
	{
		return "";
	}

	return pDataRow->ItemName;
}

//////////////////////////////////////////////////////////////////////////
// ������ ���� ��������
FName UDT_Item::GetItemDesc(int32 nItemUnique)
{
	FItemTextData* pDataRow = GetItemTextData(nItemUnique);
	if (nullptr == pDataRow)
	{
		return "";
	}

	return pDataRow->ItemDesc;
}
