// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestTwo/Public/FSerialThread.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFSerialThread() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTTWO_API UClass* Z_Construct_UClass_AFSerialThread();
TESTTWO_API UClass* Z_Construct_UClass_AFSerialThread_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestTwo();
// End Cross Module References

// Begin Class AFSerialThread
void AFSerialThread::StaticRegisterNativesAFSerialThread()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFSerialThread);
UClass* Z_Construct_UClass_AFSerialThread_NoRegister()
{
	return AFSerialThread::StaticClass();
}
struct Z_Construct_UClass_AFSerialThread_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "FSerialThread.h" },
		{ "ModuleRelativePath", "Public/FSerialThread.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFSerialThread>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AFSerialThread_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestTwo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFSerialThread_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFSerialThread_Statics::ClassParams = {
	&AFSerialThread::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFSerialThread_Statics::Class_MetaDataParams), Z_Construct_UClass_AFSerialThread_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFSerialThread()
{
	if (!Z_Registration_Info_UClass_AFSerialThread.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFSerialThread.OuterSingleton, Z_Construct_UClass_AFSerialThread_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFSerialThread.OuterSingleton;
}
template<> TESTTWO_API UClass* StaticClass<AFSerialThread>()
{
	return AFSerialThread::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFSerialThread);
AFSerialThread::~AFSerialThread() {}
// End Class AFSerialThread

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_FSerialThread_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFSerialThread, AFSerialThread::StaticClass, TEXT("AFSerialThread"), &Z_Registration_Info_UClass_AFSerialThread, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFSerialThread), 4056799115U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_FSerialThread_h_502726683(TEXT("/Script/TestTwo"),
	Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_FSerialThread_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_FSerialThread_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
