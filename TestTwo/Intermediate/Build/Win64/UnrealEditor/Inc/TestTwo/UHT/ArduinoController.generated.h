// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ArduinoController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TESTTWO_ArduinoController_generated_h
#error "ArduinoController.generated.h already included, missing '#pragma once' in ArduinoController.h"
#endif
#define TESTTWO_ArduinoController_generated_h

#define FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTurnPumpOff); \
	DECLARE_FUNCTION(execTurnPumpOn);


#define FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAArduinoController(); \
	friend struct Z_Construct_UClass_AArduinoController_Statics; \
public: \
	DECLARE_CLASS(AArduinoController, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestTwo"), NO_API) \
	DECLARE_SERIALIZER(AArduinoController)


#define FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AArduinoController(AArduinoController&&); \
	AArduinoController(const AArduinoController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AArduinoController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AArduinoController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AArduinoController) \
	NO_API virtual ~AArduinoController();


#define FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_11_PROLOG
#define FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TESTTWO_API UClass* StaticClass<class AArduinoController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Thomas_Documents_Unreal_Projects_TestTwo_Source_TestTwo_Public_ArduinoController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
