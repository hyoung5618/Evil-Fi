#include "DT_Item.h"

#include "ConstructorHelpers.h"

#include "Common/CommonLog.h"

//////////////////////////////////////////////////////////////////////////
// AItemDataTables
UDT_Item::UDT_Item()
{
	// Item관련 데이터가 정의된 데이터 테이블을 읽어옵니다.

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
// 아이템 데이터 반환
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
// 아이템 텍스트 데이터 반환
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
// 아이템 값 가져오기
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
// 아이템 이름 가져오기
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
// 아이템 설명 가져오기
FName UDT_Item::GetItemDesc(int32 nItemUnique)
{
	FItemTextData* pDataRow = GetItemTextData(nItemUnique);
	if (nullptr == pDataRow)
	{
		return "";
	}

	return pDataRow->ItemDesc;
}
