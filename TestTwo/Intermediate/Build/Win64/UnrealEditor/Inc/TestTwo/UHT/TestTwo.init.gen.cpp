// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestTwo_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_TestTwo;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_TestTwo()
	{
		if (!Z_Registration_Info_UPackage__Script_TestTwo.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/TestTwo",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xA15665B0,
				0x39BCE2A9,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_TestTwo.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_TestTwo.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_TestTwo(Z_Construct_UPackage__Script_TestTwo, TEXT("/Script/TestTwo"), Z_Registration_Info_UPackage__Script_TestTwo, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xA15665B0, 0x39BCE2A9));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
