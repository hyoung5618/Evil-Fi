// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/*
	USTRUCT(BlueprintType) : 이 구조체를 블루프린트에서 변수로 사용할 수 있는 유형으로 노출시킵니다.

	<구조체>
	https://docs.unrealengine.com/ko/Programming/UnrealArchitecture/Reference/Structs/index.html
*/
USTRUCT(BlueprintType)
struct FActionInputCallbackConfig
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "UI")
		FName m_ActionName;

	UPROPERTY(EditAnywhere, Category = "UI")
		FName m_CallbackName;

	// Consume : 우선 순위가 낮은 액터가 이 입력을 처리하지 못하게합니다.
	UPROPERTY(EditAnywhere, Category = "UI")
		bool m_bConsume;

	// TEnumAsByte : 열거 형 값을 형식이 안전한 방식인 바이트로 저장하는 템플릿입니다.
	UPROPERTY(EditAnywhere, Category = "UI")
		TEnumAsByte<EInputEvent> m_InputEvent;
};

USTRUCT(BlueprintType)
struct FAxisInputCallbackConfig
{
	GENERATED_USTRUCT_BODY()

public:
	FAxisInputCallbackConfig()
		: m_fScale(1.f)
	{}

	UPROPERTY(EditAnywhere, Category = "UI")
		FName m_AxisName;

	UPROPERTY(EditAnywhere, Category = "UI")
		float m_fScale;

	UPROPERTY(EditAnywhere, Category = "UI")
		FName m_CallbackName;

	UPROPERTY(EditAnywhere, Category = "UI")
		bool m_bConsume;
};

//UCLASS()
//class EVIL_FI_API UBaseUserWidget : public UUserWidget
//{
//	GENERATED_BODY()
//	
//public:
//	virtual void SetWidgetName(const FString& strWidgetName) {}
//
//protected:
//	//virtual void NativeConstruct() override;
//	virtual void NativeSetupInput();
//
//	void BindNewActionCallBacks(TArray<FActionInputCallbackConfig> arrCallbackConfigs);
//	void UnbindActionCallBacks(TArray<FActionInputCallbackConfig> arrCallbackConfigs);
//	
//	void BindNewAxisCallBacks(TArray<FAxisInputCallbackConfig> arrCallbackConfigs);
//
//	// UFUNCTION(BlueprintImplementableEvent) : 이 함수는 블루프린트 또는 레벨 블루프린트 그래프에서 구현할 수 있습니다.
//	//UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
//	//void SetupInputForBlueprint();
//
//public:
//	UFUNCTION(BlueprintCallable, Category = "UI")
//	void ListenForInputAxis(FName AxisName, float fScale, bool bConsume/*, FOnInputAxis Callback*/);
//
//	//UFUNCTION(BlueprintCallable, Category = "UI");
//	//float GetRawKeyValue(/*FKey InKey*/);
//
//	//UFUNCTION(BlueprintCallable, Category = "Input");
//	//void StopListeningForAllInputAxises();
//
//	void OnInputAxis(float Scale/*, FOnInputAxis CallBack*/);
//};
