// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestTwo/Public/ArduinoController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArduinoController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTTWO_API UClass* Z_Construct_UClass_AArduinoController();
TESTTWO_API UClass* Z_Construct_UClass_AArduinoController_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestTwo();
// End Cross Module References

// Begin Class AArduinoController Function TurnPumpOff
struct Z_Construct_UFunction_AArduinoController_TurnPumpOff_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Arduino" },
		{ "ModuleRelativePath", "Public/ArduinoController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AArduinoController_TurnPumpOff_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AArduinoController, nullptr, "TurnPumpOff", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArduinoController_TurnPumpOff_Statics::Function_MetaDataParams), Z_Construct_UFunction_AArduinoController_TurnPumpOff_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AArduinoController_TurnPumpOff()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AArduinoController_TurnPumpOff_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AArduinoController::execTurnPumpOff)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TurnPumpOff();
	P_NATIVE_END;
}
// End Class AArduinoController Function TurnPumpOff

// Begin Class AArduinoController Function TurnPumpOn
struct Z_Construct_UFunction_AArduinoController_TurnPumpOn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Arduino" },
		{ "ModuleRelativePath", "Public/ArduinoController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AArduinoController_TurnPumpOn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AArduinoController, nullptr, "TurnPumpOn", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArduinoController_TurnPumpOn_Statics::Function_MetaDataParams), Z_Construct_UFunction_AArduinoController_TurnPumpOn_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AArduinoController_TurnPumpOn()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AArduinoController_TurnPumpOn_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AArduinoController::execTurnPumpOn)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TurnPumpOn();
	P_NATIVE_END;
}
// End Class AArduinoController Function TurnPumpOn

// Begin Class AArduinoController
void AArduinoController::StaticRegisterNativesAArduinoController()
{
	UClass* Class = AArduinoController::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "TurnPumpOff", &AArduinoController::execTurnPumpOff },
		{ "TurnPumpOn", &AArduinoController::execTurnPumpOn },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AArduinoController);
UClass* Z_Construct_UClass_AArduinoController_NoRegister()
{
	return AArduinoController::StaticClass();
}
struct Z_Construct_UClass_AArduinoController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ArduinoController.h" },
		{ "ModuleRelativePath", "Public/ArduinoController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AArduinoController_TurnPumpOff, "TurnPumpOff" }, // 4000380532
		{ &Z_Construct_UFunction_AArduinoController_TurnPumpOn, "TurnPumpOn" }, // 1582755206
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AArduinoController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AArduinoController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestTwo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AArduinoController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AArduinoController_Statics::ClassParams = {
	&AArduinoController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArduinoController_Statics::Class_MetaDataParams), Z_Construct_UClass_AArduinoController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AArduinoController()
{
	if (!Z_Registration_Info_UClass_AArduinoController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AArduinoController.OuterSingleton, Z_Construct_UClass_AArduinoController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AArduinoController.OuterSingleton;
}
template<> TESTTWO_API UClass* StaticClass<AArduinoController>()
{
	return AArduinoController::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AArduinoController);
AArduinoController::~AArduinoController() {}
// End Class AArduinoController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_ArduinoController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AArduinoController, AArduinoController::StaticClass, TEXT("AArduinoController"), &Z_Registration_Info_UClass_AArduinoController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AArduinoController), 4173515151U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_ArduinoController_h_2925387586(TEXT("/Script/TestTwo"),
	Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_ArduinoController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_ArduinoController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
