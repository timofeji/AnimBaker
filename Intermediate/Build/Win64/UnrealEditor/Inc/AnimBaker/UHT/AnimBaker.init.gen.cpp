// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimBaker_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_AnimBaker;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_AnimBaker()
	{
		if (!Z_Registration_Info_UPackage__Script_AnimBaker.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/AnimBaker",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000040,
				0x95E69DD0,
				0x49978065,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_AnimBaker.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_AnimBaker.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_AnimBaker(Z_Construct_UPackage__Script_AnimBaker, TEXT("/Script/AnimBaker"), Z_Registration_Info_UPackage__Script_AnimBaker, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x95E69DD0, 0x49978065));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
