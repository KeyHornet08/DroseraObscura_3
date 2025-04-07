// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestTwo/Public/AControlServoActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAControlServoActor() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTTWO_API UClass* Z_Construct_UClass_AControlServoActor();
TESTTWO_API UClass* Z_Construct_UClass_AControlServoActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestTwo();
// End Cross Module References

// Begin Class AControlServoActor
void AControlServoActor::StaticRegisterNativesAControlServoActor()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AControlServoActor);
UClass* Z_Construct_UClass_AControlServoActor_NoRegister()
{
	return AControlServoActor::StaticClass();
}
struct Z_Construct_UClass_AControlServoActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "AControlServoActor.h" },
		{ "ModuleRelativePath", "Public/AControlServoActor.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AControlServoActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AControlServoActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestTwo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AControlServoActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AControlServoActor_Statics::ClassParams = {
	&AControlServoActor::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AControlServoActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AControlServoActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AControlServoActor()
{
	if (!Z_Registration_Info_UClass_AControlServoActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AControlServoActor.OuterSingleton, Z_Construct_UClass_AControlServoActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AControlServoActor.OuterSingleton;
}
template<> TESTTWO_API UClass* StaticClass<AControlServoActor>()
{
	return AControlServoActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AControlServoActor);
AControlServoActor::~AControlServoActor() {}
// End Class AControlServoActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_AControlServoActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AControlServoActor, AControlServoActor::StaticClass, TEXT("AControlServoActor"), &Z_Registration_Info_UClass_AControlServoActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AControlServoActor), 2371271768U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_AControlServoActor_h_2129966953(TEXT("/Script/TestTwo"),
	Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_AControlServoActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_AControlServoActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
