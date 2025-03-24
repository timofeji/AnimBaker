// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnimBaker.h"

#ifdef ANIMBAKER_AnimBaker_generated_h
#error "AnimBaker.generated.h already included, missing '#pragma once' in AnimBaker.h"
#endif
#define ANIMBAKER_AnimBaker_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UAnimBakeTarget **********************************************************
#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAnimBakeTarget(); \
	friend struct Z_Construct_UClass_UAnimBakeTarget_Statics; \
public: \
	DECLARE_CLASS(UAnimBakeTarget, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnimBaker"), ANIMBAKER_API) \
	DECLARE_SERIALIZER(UAnimBakeTarget)


#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ANIMBAKER_API UAnimBakeTarget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAnimBakeTarget(UAnimBakeTarget&&); \
	UAnimBakeTarget(const UAnimBakeTarget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ANIMBAKER_API, UAnimBakeTarget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnimBakeTarget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnimBakeTarget) \
	ANIMBAKER_API virtual ~UAnimBakeTarget();


#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_9_PROLOG
#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_12_INCLASS_NO_PURE_DECLS \
	FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAnimBakeTarget;

// ********** End Class UAnimBakeTarget ************************************************************

// ********** Begin ScriptStruct FBakeResult *******************************************************
#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_34_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBakeResult_Statics; \
	ANIMBAKER_API static class UScriptStruct* StaticStruct();


struct FBakeResult;
// ********** End ScriptStruct FBakeResult *********************************************************

// ********** Begin Class UAnimBaker ***************************************************************
#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_45_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAnimBaker(); \
	friend struct Z_Construct_UClass_UAnimBaker_Statics; \
public: \
	DECLARE_CLASS(UAnimBaker, UAssetUserData, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnimBaker"), ANIMBAKER_API) \
	DECLARE_SERIALIZER(UAnimBaker)


#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_45_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ANIMBAKER_API UAnimBaker(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAnimBaker(UAnimBaker&&); \
	UAnimBaker(const UAnimBaker&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ANIMBAKER_API, UAnimBaker); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnimBaker); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnimBaker) \
	ANIMBAKER_API virtual ~UAnimBaker();


#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_42_PROLOG
#define FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_45_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_45_INCLASS_NO_PURE_DECLS \
	FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h_45_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAnimBaker;

// ********** End Class UAnimBaker *****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
