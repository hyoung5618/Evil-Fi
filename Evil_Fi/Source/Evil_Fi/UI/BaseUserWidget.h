// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/*
	USTRUCT(BlueprintType) : �� ����ü�� �������Ʈ���� ������ ����� �� �ִ� �������� �����ŵ�ϴ�.

	<����ü>
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

	//// Consume : �켱 ������ ���� ���Ͱ� �� �Է��� ó������ ���ϰ��մϴ�.
	//UPROPERTY(EditAnyhwere, Category = "UI")
	//bool m_bConsume;

	//// TEnumAsByte : ���� �� ���� ������ ������ ����� ����Ʈ�� �����ϴ� ���ø��Դϴ�.
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
	UCLASS(Config == ) : �� Ŭ������ ȯ�漳�� (.ini)���Ͽ� �����͸� ������ �� ������ ��Ÿ���ϴ�.
	config �Ǵ� globalconfig �����ڷ� ����� Ŭ���� ������Ƽ�� �ִ� ���, �� �����ڴ� �� ������Ƽ��
	�ش� �̸��� ȯ�� ���� ���Ͽ� �����ϵ��� �մϴ�. �� �����ڴ� ��� �ڽ� Ŭ������ ���ĵǸ�
	��ȿȭ��ų �� ������, �ڽ� Ŭ���������� ȯ�漳�� ������ �ٲ� ���� �ֽ��ϴ�.
	config �����ڿ� �ٸ� ConfigName���� �ٽ� �������ָ� �˴ϴ�.
	�Ϲ����� ConfigName ���� "Engine", "Editor", "Input", "Game" �Դϴ�.

	<Ŭ���� ������>
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
//	// UFUNCTION(BlueprintImplementableEvent) : �� �Լ��� �������Ʈ �Ǵ� ���� �������Ʈ �׷������� ������ �� �ֽ��ϴ�.
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
