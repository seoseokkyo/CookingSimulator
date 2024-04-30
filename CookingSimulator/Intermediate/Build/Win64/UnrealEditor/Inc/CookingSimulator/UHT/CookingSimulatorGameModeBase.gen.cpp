// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CookingSimulator/Public/CookingSimulatorGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCookingSimulatorGameModeBase() {}
// Cross Module References
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_ACookingSimulatorGameModeBase();
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_ACookingSimulatorGameModeBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_CookingSimulator();
// End Cross Module References
	void ACookingSimulatorGameModeBase::StaticRegisterNativesACookingSimulatorGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACookingSimulatorGameModeBase);
	UClass* Z_Construct_UClass_ACookingSimulatorGameModeBase_NoRegister()
	{
		return ACookingSimulatorGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_CookingSimulator,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CookingSimulatorGameModeBase.h" },
		{ "ModuleRelativePath", "Public/CookingSimulatorGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACookingSimulatorGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::ClassParams = {
		&ACookingSimulatorGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACookingSimulatorGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ACookingSimulatorGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACookingSimulatorGameModeBase.OuterSingleton, Z_Construct_UClass_ACookingSimulatorGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACookingSimulatorGameModeBase.OuterSingleton;
	}
	template<> COOKINGSIMULATOR_API UClass* StaticClass<ACookingSimulatorGameModeBase>()
	{
		return ACookingSimulatorGameModeBase::StaticClass();
	}
	ACookingSimulatorGameModeBase::ACookingSimulatorGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACookingSimulatorGameModeBase);
	ACookingSimulatorGameModeBase::~ACookingSimulatorGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingSimulatorGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingSimulatorGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACookingSimulatorGameModeBase, ACookingSimulatorGameModeBase::StaticClass, TEXT("ACookingSimulatorGameModeBase"), &Z_Registration_Info_UClass_ACookingSimulatorGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACookingSimulatorGameModeBase), 2786505072U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingSimulatorGameModeBase_h_603382693(TEXT("/Script/CookingSimulator"),
		Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingSimulatorGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_CookingSimulatorGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
