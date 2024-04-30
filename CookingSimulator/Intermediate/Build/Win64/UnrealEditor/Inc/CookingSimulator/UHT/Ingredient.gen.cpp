// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CookingSimulator/Public/Ingredient.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeIngredient() {}
// Cross Module References
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_AIngredient();
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_AIngredient_NoRegister();
	COOKINGSIMULATOR_API UClass* Z_Construct_UClass_AItem();
	UPackage* Z_Construct_UPackage__Script_CookingSimulator();
// End Cross Module References
	void AIngredient::StaticRegisterNativesAIngredient()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AIngredient);
	UClass* Z_Construct_UClass_AIngredient_NoRegister()
	{
		return AIngredient::StaticClass();
	}
	struct Z_Construct_UClass_AIngredient_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AIngredient_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AItem,
		(UObject* (*)())Z_Construct_UPackage__Script_CookingSimulator,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIngredient_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIngredient_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Ingredient.h" },
		{ "ModuleRelativePath", "Public/Ingredient.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AIngredient_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIngredient>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AIngredient_Statics::ClassParams = {
		&AIngredient::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AIngredient_Statics::Class_MetaDataParams), Z_Construct_UClass_AIngredient_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AIngredient()
	{
		if (!Z_Registration_Info_UClass_AIngredient.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AIngredient.OuterSingleton, Z_Construct_UClass_AIngredient_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AIngredient.OuterSingleton;
	}
	template<> COOKINGSIMULATOR_API UClass* StaticClass<AIngredient>()
	{
		return AIngredient::StaticClass();
	}
	AIngredient::AIngredient() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AIngredient);
	AIngredient::~AIngredient() {}
	struct Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_Ingredient_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_Ingredient_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AIngredient, AIngredient::StaticClass, TEXT("AIngredient"), &Z_Registration_Info_UClass_AIngredient, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AIngredient), 504905833U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_Ingredient_h_2193990305(TEXT("/Script/CookingSimulator"),
		Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_Ingredient_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_admin_Desktop_Project_CookingSimulator_CookingSimulator_Source_CookingSimulator_Public_Ingredient_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
