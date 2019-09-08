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

	//UPROPERTY(EditAnywhere, Category = "UI")
	//FName m_ActionName;

	//UPROPERTY(EditAnywhere, Category = "UI")
	//FName m_CallbackName;

	//// Consume : 우선 순위가 낮은 액터가 이 입력을 처리하지 못하게합니다.
	//UPROPERTY(EditAnyhwere, Category = "UI")
	//bool m_bConsume;

	//// TEnumAsByte : 열거 형 값을 형식이 안전한 방식인 바이트로 저장하는 템플릿입니다.
	//UPROPERTY(EditAnyhwere, Category = "UI")
	//TEnumAsByte<EInputEvent> m_InputEvent;
};

USTRUCT(BlueprintType)
struct FAxisInputCallbackConfig
{
	GENERATED_USTRUCT_BODY()
		
//public:
//	FAxisInputCallbackConfig()
//		: m_fScale(1.f)
//	{}

	//UPROPERTY(EditAnyhwere, Category = "UI")
	//FName m_AxisName;

	//UPROPERTY(EditAnyhwere, Category = "UI")
	//float m_fScale;

	//UPROPERTY(EditAnyhwere, Category = "UI")
	//FName m_CallbackName;

	//UPROPERTY(EditAnywhere, Category = "UI")
	//bool m_bConsume;
};

/*
	UCLASS(Config == ) : 이 클래스는 환경설정 (.ini)파일에 데이터를 저장할 수 있음을 나타냅니다.
	config 또는 globalconfig 지정자로 선언된 클래스 프로퍼티가 있는 경우, 이 지정자는 그 프로퍼티를
	해당 이름의 환경 설정 파일에 저장하도록 합니다. 이 지정자는 모든 자식 클래스에 전파되며
	무효화시킬 수 없으나, 자식 클래스에서는 환경설정 파일을 바꿀 수는 있습니다.
	config 지정자에 다른 ConfigName으로 다시 선언해주면 됩니다.
	일반적인 ConfigName 값은 "Engine", "Editor", "Input", "Game" 입니다.

	<클래스 지정자>
	https://docs.unrealengine.com/ko/Programming/UnrealArchitecture/Reference/Classes/Specifiers/index.html
*/
//UCLASS(Config = Game)
class EVIL_FI_API UBaseUserWidget// : public UUserWidget
{
	//GENERATED_BODY()
	
//public:
//	virtual void SetWidgetName(const FString& strWidgetName) {}
//
//protected:
//	virtual void NativeConstruct() override;
//	virtual void NativeSetupInput();
//
//	void BindNewActionCallBacks(TArray<FActionInputCallbackConfig> arrCallbackConfigs);
//	void UnbindActionCallBacks(TArray<FActionInputCallbackConfig> arrCallbackConfigs);
//	
//	void BindNewAxisCallBacks(TArray<FAxisInputCallbackConfig> arrCallbackConfigs);
//
//	// UFUNCTION(BlueprintImplementableEvent) : 이 함수는 블루프린트 또는 레벨 블루프린트 그래프에서 구현할 수 있습니다.
//	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
//	void SetupInputForBlueprint();
//
//public:
//	UFUNCTION(BlueprintCallable, Category = "UI")
//	void ListenForInputAxis(FName AxisName, float fScale, bool bConsume, FOnInputAxis Callback);
//
//	UFUNCTION(BluerpintCallabe, Category = "UI")
//	float GetRawKeyValue(FKey InKey);
//
//	UFUNCTION(BlueprintCallabe, Category = "Input")
//	void StopListeningForAllInputAxises();
//
//	void OnInputAxis(float Scale, FOnInputAxis CallBack);
//
//
};
