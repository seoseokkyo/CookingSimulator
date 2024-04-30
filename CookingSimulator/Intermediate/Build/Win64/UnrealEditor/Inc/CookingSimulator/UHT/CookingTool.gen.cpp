// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CookingSimulator/Public/CookingTool.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCookingTool() {}
// Cross Module References
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_ACookingTool();
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_ACookingTool_NoRegister();
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_AItem();
	UPackage* Z_Construct_UPackage__Script_CookingSimulator();
// End Cross Module References
	void ACookingTool::StaticRegisterNativesACookingTool()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACookingTool);
	UClass* Z_Construct_UClass_ACookingTool_NoRegister()
	{
		return ACookingTool::StaticClass();
	}
	struct Z_Construct_UClass_ACookingTool_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACookingTool_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AItem,
		(UObject* (*)())Z_Construct_UPackage__Script_CookingSimulator,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACookingTool_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACookingTool_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "CookingTool.h" },
		{ "ModuleRelativePath", "Public/CookingTool.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACookingTool_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACookingTool>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACookingTool_Statics::ClassParams = {
		&ACookingTool::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACookingTool_Statics::Class_MetaDataParams), Z_Construct_UClass_ACookingTool_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACookingTool()
	{
		if (!Z_Registration_Info_UClass_ACookingTool.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACookingTool.OuterSingleton, Z_Construct_UClass_ACookingTool_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACookingTool.OuterSingleton;
	}
	template<> COOKINGSIMULATOR_API UClass* StaticClass<ACookingTool>()
	{
		return ACookingTool::StaticClass();
	}
	ACookingTool::ACookingTool() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACookingTool);
	ACookingTool::~ACookingTool() {}
	struct Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingTool_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingTool_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACookingTool, ACookingTool::StaticClass, TEXT("ACookingTool"), &Z_Registration_Info_UClass_ACookingTool, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACookingTool), 1310662036U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingTool_h_85993870(TEXT("/Script/CookingSimulator"),
		Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingTool_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingTool_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
