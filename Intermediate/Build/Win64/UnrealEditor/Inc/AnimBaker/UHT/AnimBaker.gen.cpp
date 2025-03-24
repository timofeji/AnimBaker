// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimBaker/AnimBaker.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAnimBaker() {}

// ********** Begin Cross Module References ********************************************************
ANIMBAKER_API UClass* Z_Construct_UClass_UAnimBaker();
ANIMBAKER_API UClass* Z_Construct_UClass_UAnimBaker_NoRegister();
ANIMBAKER_API UClass* Z_Construct_UClass_UAnimBakeTarget();
ANIMBAKER_API UClass* Z_Construct_UClass_UAnimBakeTarget_NoRegister();
ANIMBAKER_API UScriptStruct* Z_Construct_UScriptStruct_FBakeResult();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
ENGINE_API UClass* Z_Construct_UClass_UAssetUserData();
MOVIESCENE_API UClass* Z_Construct_UClass_UMovieSceneSection_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UAnimSeqExportOption_NoRegister();
UPackage* Z_Construct_UPackage__Script_AnimBaker();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAnimBakeTarget **********************************************************
void UAnimBakeTarget::StaticRegisterNativesUAnimBakeTarget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimBakeTarget;
UClass* UAnimBakeTarget::GetPrivateStaticClass()
{
	using TClass = UAnimBakeTarget;
	if (!Z_Registration_Info_UClass_UAnimBakeTarget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AnimBakeTarget"),
			Z_Registration_Info_UClass_UAnimBakeTarget.InnerSingleton,
			StaticRegisterNativesUAnimBakeTarget,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UAnimBakeTarget.InnerSingleton;
}
UClass* Z_Construct_UClass_UAnimBakeTarget_NoRegister()
{
	return UAnimBakeTarget::StaticClass();
}
struct Z_Construct_UClass_UAnimBakeTarget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "AnimBaker.h" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Guid_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetPath_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLinkToAsset_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsLocked_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportOptionsPtr_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveSections_MetaData[] = {
		{ "Category", "BakerTarget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Guid;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetPath;
	static void NewProp_bLinkToAsset_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLinkToAsset;
	static void NewProp_bIsLocked_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsLocked;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ExportOptionsPtr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveSections_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActiveSections;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimBakeTarget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_Guid = { "Guid", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBakeTarget, Guid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Guid_MetaData), NewProp_Guid_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBakeTarget, AssetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetName_MetaData), NewProp_AssetName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_AssetPath = { "AssetPath", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBakeTarget, AssetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetPath_MetaData), NewProp_AssetPath_MetaData) };
void Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bLinkToAsset_SetBit(void* Obj)
{
	((UAnimBakeTarget*)Obj)->bLinkToAsset = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bLinkToAsset = { "bLinkToAsset", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAnimBakeTarget), &Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bLinkToAsset_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLinkToAsset_MetaData), NewProp_bLinkToAsset_MetaData) };
void Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bIsLocked_SetBit(void* Obj)
{
	((UAnimBakeTarget*)Obj)->bIsLocked = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bIsLocked = { "bIsLocked", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAnimBakeTarget), &Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bIsLocked_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsLocked_MetaData), NewProp_bIsLocked_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ExportOptionsPtr = { "ExportOptionsPtr", nullptr, (EPropertyFlags)0x0114000000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBakeTarget, ExportOptionsPtr), Z_Construct_UClass_UAnimSeqExportOption_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportOptionsPtr_MetaData), NewProp_ExportOptionsPtr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ActiveSections_Inner = { "ActiveSections", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UMovieSceneSection_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ActiveSections = { "ActiveSections", nullptr, (EPropertyFlags)0x001000800000000c, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBakeTarget, ActiveSections), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveSections_MetaData), NewProp_ActiveSections_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnimBakeTarget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_Guid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_AssetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_AssetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bLinkToAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_bIsLocked,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ExportOptionsPtr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ActiveSections_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBakeTarget_Statics::NewProp_ActiveSections,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBakeTarget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAnimBakeTarget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_AnimBaker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBakeTarget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnimBakeTarget_Statics::ClassParams = {
	&UAnimBakeTarget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAnimBakeTarget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBakeTarget_Statics::PropPointers),
	0,
	0x008800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBakeTarget_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnimBakeTarget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAnimBakeTarget()
{
	if (!Z_Registration_Info_UClass_UAnimBakeTarget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimBakeTarget.OuterSingleton, Z_Construct_UClass_UAnimBakeTarget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimBakeTarget.OuterSingleton;
}
UAnimBakeTarget::UAnimBakeTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimBakeTarget);
UAnimBakeTarget::~UAnimBakeTarget() {}
// ********** End Class UAnimBakeTarget ************************************************************

// ********** Begin ScriptStruct FBakeResult *******************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBakeResult;
class UScriptStruct* FBakeResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBakeResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBakeResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBakeResult, (UObject*)Z_Construct_UPackage__Script_AnimBaker(), TEXT("BakeResult"));
	}
	return Z_Registration_Info_UScriptStruct_FBakeResult.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBakeResult_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBakeResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBakeResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AnimBaker,
	nullptr,
	&NewStructOps,
	"BakeResult",
	nullptr,
	0,
	sizeof(FBakeResult),
	alignof(FBakeResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBakeResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBakeResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBakeResult()
{
	if (!Z_Registration_Info_UScriptStruct_FBakeResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBakeResult.InnerSingleton, Z_Construct_UScriptStruct_FBakeResult_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBakeResult.InnerSingleton;
}
// ********** End ScriptStruct FBakeResult *********************************************************

// ********** Begin Class UAnimBaker ***************************************************************
void UAnimBaker::StaticRegisterNativesUAnimBaker()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimBaker;
UClass* UAnimBaker::GetPrivateStaticClass()
{
	using TClass = UAnimBaker;
	if (!Z_Registration_Info_UClass_UAnimBaker.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AnimBaker"),
			Z_Registration_Info_UClass_UAnimBaker.InnerSingleton,
			StaticRegisterNativesUAnimBaker,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UAnimBaker.InnerSingleton;
}
UClass* Z_Construct_UClass_UAnimBaker_NoRegister()
{
	return UAnimBaker::StaticClass();
}
struct Z_Construct_UClass_UAnimBaker_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n * Holds different targets to bake from a level sequence\n */" },
#endif
		{ "IncludePath", "AnimBaker.h" },
		{ "ModuleRelativePath", "AnimBaker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* Holds different targets to bake from a level sequence" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimBakeTargets_MetaData[] = {
		{ "Category", "Baker" },
		{ "ModuleRelativePath", "AnimBaker.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimBakeTargets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AnimBakeTargets;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimBaker>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAnimBaker_Statics::NewProp_AnimBakeTargets_Inner = { "AnimBakeTargets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UAnimBaker_Statics::NewProp_AnimBakeTargets = { "AnimBakeTargets", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimBaker, AnimBakeTargets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimBakeTargets_MetaData), NewProp_AnimBakeTargets_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnimBaker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBaker_Statics::NewProp_AnimBakeTargets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimBaker_Statics::NewProp_AnimBakeTargets,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBaker_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAnimBaker_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAssetUserData,
	(UObject* (*)())Z_Construct_UPackage__Script_AnimBaker,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBaker_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnimBaker_Statics::ClassParams = {
	&UAnimBaker::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAnimBaker_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBaker_Statics::PropPointers),
	0,
	0x002810A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimBaker_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnimBaker_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAnimBaker()
{
	if (!Z_Registration_Info_UClass_UAnimBaker.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimBaker.OuterSingleton, Z_Construct_UClass_UAnimBaker_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimBaker.OuterSingleton;
}
UAnimBaker::UAnimBaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimBaker);
UAnimBaker::~UAnimBaker() {}
// ********** End Class UAnimBaker *****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBakeResult::StaticStruct, Z_Construct_UScriptStruct_FBakeResult_Statics::NewStructOps, TEXT("BakeResult"), &Z_Registration_Info_UScriptStruct_FBakeResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBakeResult), 2322339309U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimBakeTarget, UAnimBakeTarget::StaticClass, TEXT("UAnimBakeTarget"), &Z_Registration_Info_UClass_UAnimBakeTarget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimBakeTarget), 2718681261U) },
		{ Z_Construct_UClass_UAnimBaker, UAnimBaker::StaticClass, TEXT("UAnimBaker"), &Z_Registration_Info_UClass_UAnimBaker, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimBaker), 1480712857U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_2649319100(TEXT("/Script/AnimBaker"),
	Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_hb_game_Plugins_AnimBaker_Source_AnimBaker_AnimBaker_h__Script_AnimBaker_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
