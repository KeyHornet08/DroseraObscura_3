// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestTwo/Public/StepperControl.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStepperControl() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTTWO_API UClass* Z_Construct_UClass_AStepperControl();
TESTTWO_API UClass* Z_Construct_UClass_AStepperControl_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestTwo();
// End Cross Module References

// Begin Class AStepperControl
void AStepperControl::StaticRegisterNativesAStepperControl()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AStepperControl);
UClass* Z_Construct_UClass_AStepperControl_NoRegister()
{
	return AStepperControl::StaticClass();
}
struct Z_Construct_UClass_AStepperControl_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "StepperControl.h" },
		{ "ModuleRelativePath", "Public/StepperControl.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStepperControl>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AStepperControl_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestTwo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStepperControl_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AStepperControl_Statics::ClassParams = {
	&AStepperControl::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AStepperControl_Statics::Class_MetaDataParams), Z_Construct_UClass_AStepperControl_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AStepperControl()
{
	if (!Z_Registration_Info_UClass_AStepperControl.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AStepperControl.OuterSingleton, Z_Construct_UClass_AStepperControl_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AStepperControl.OuterSingleton;
}
template<> TESTTWO_API UClass* StaticClass<AStepperControl>()
{
	return AStepperControl::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AStepperControl);
// End Class AStepperControl

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_StepperControl_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AStepperControl, AStepperControl::StaticClass, TEXT("AStepperControl"), &Z_Registration_Info_UClass_AStepperControl, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AStepperControl), 4274487763U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_StepperControl_h_498981444(TEXT("/Script/TestTwo"),
	Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_StepperControl_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_DroseraObscura_3_TestTwo_Source_TestTwo_Public_StepperControl_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
