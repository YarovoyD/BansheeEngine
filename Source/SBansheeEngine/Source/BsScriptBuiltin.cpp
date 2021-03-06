//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsScriptBuiltin.h"
#include "BsMonoManager.h"
#include "BsMonoClass.h"
#include "BsMonoMethod.h"
#include "BsMonoUtil.h"
#include "BsBuiltinResources.h"
#include "BsScriptSpriteTexture.h"
#include "BsScriptShader.h"
#include "BsScriptMesh.h"
#include "BsScriptResourceManager.h"

namespace BansheeEngine
{
	ScriptBuiltin::ScriptBuiltin(MonoObject* instance)
		:ScriptObject(instance)
	{ }

	void ScriptBuiltin::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_GetWhiteTexture", &ScriptBuiltin::internal_GetWhiteTexture);
		metaData.scriptClass->addInternalCall("Internal_GetDiffuseShader", &ScriptBuiltin::internal_GetDiffuseShader);
		metaData.scriptClass->addInternalCall("Internal_GetMesh", &ScriptBuiltin::internal_GetMesh);
	}

	MonoObject* ScriptBuiltin::internal_GetWhiteTexture()
	{
		HSpriteTexture whiteTexture = BuiltinResources::instance().getWhiteSpriteTexture();

		ScriptSpriteTexture* scriptSpriteTex;
		ScriptResourceManager::instance().getScriptResource(whiteTexture, &scriptSpriteTex, true);

		return scriptSpriteTex->getManagedInstance();
	}

	MonoObject* ScriptBuiltin::internal_GetDiffuseShader()
	{
		HShader diffuseShader = BuiltinResources::instance().getDiffuseShader();

		ScriptShader* scriptShader;
		ScriptResourceManager::instance().getScriptResource(diffuseShader, &scriptShader, true);

		return scriptShader->getManagedInstance();
	}

	MonoObject* ScriptBuiltin::internal_GetMesh(BuiltinMesh meshType)
	{
		HMesh mesh = BuiltinResources::instance().getMesh(meshType);

		ScriptMesh* scriptMesh;
		ScriptResourceManager::instance().getScriptResource(mesh, &scriptMesh, true);

		return scriptMesh->getManagedInstance();
	}
}