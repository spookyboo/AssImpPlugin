/*
  -----------------------------------------------------------------------------
  This source file is part of OGRE
  (Object-oriented Graphics Rendering Engine)
  For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  -----------------------------------------------------------------------------
*/

#include "OgreRoot.h"
#include "AssImpPlugin.h"
#include "OgreLogManager.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Ogre
{
	static const String gImportMenuText = "Import a non-Ogre model";
	static const String gExportMenuText = "";
	//---------------------------------------------------------------------
	AssImpPlugin::AssImpPlugin()
    {
    }
    //---------------------------------------------------------------------
    const String& AssImpPlugin::getName() const
    {
        return GENERAL_HLMS_PLUGIN_NAME;
    }
    //---------------------------------------------------------------------
    void AssImpPlugin::install()
    {
    }
    //---------------------------------------------------------------------
    void AssImpPlugin::initialise()
    {
        // nothing to do
	}
    //---------------------------------------------------------------------
    void AssImpPlugin::shutdown()
    {
        // nothing to do
    }
    //---------------------------------------------------------------------
    void AssImpPlugin::uninstall()
    {
    }
	//---------------------------------------------------------------------
	bool AssImpPlugin::isOpenFileDialogForImport(void) const
	{
		return true;
	}
	//---------------------------------------------------------------------
	bool AssImpPlugin::isImport (void) const
	{
		return true;
	}
	//---------------------------------------------------------------------
	bool AssImpPlugin::isOpenFileDialogForExport(void) const
	{
		return false;
	}
	//---------------------------------------------------------------------
	bool AssImpPlugin::isExport (void) const
	{
		return false;
	}
	//---------------------------------------------------------------------
	void AssImpPlugin::performPreImportActions(void)
	{
		// Nothing to do
	}
	//---------------------------------------------------------------------
	void AssImpPlugin::performPostImportActions(void)
	{
		// Nothing to do
	}
	//---------------------------------------------------------------------
	void AssImpPlugin::performPreExportActions(void)
	{
		// Nothing to do
	}
	//---------------------------------------------------------------------
	void AssImpPlugin::performPostExportActions(void)
	{
		// Nothing to do
	}
	//---------------------------------------------------------------------
	unsigned int AssImpPlugin::getActionFlag(void)
	{
		return 0;
	}

	//---------------------------------------------------------------------
	const String& AssImpPlugin::getImportMenuText (void) const
	{
		return gImportMenuText;
	}
	//---------------------------------------------------------------------
	const String& AssImpPlugin::getExportMenuText (void) const
	{
		return gExportMenuText;
	}
	//---------------------------------------------------------------------
	bool AssImpPlugin::isTexturesUsedByDatablocksForExport(void) const
	{
		return false;
	}
	//---------------------------------------------------------------------
	bool AssImpPlugin::executeImport (HlmsEditorPluginData* data)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(data->mInFileDialogName,
			aiProcessPreset_TargetRealtime_Quality |
			aiProcess_TransformUVCoords |
			aiProcess_FlipUVs);

		if (!scene)
		{
			data->mOutErrorText = "Could not import " + data->mInFileDialogName;
			LogManager::getSingleton().logMessage(importer.GetErrorString());
			return false;
		}

		if (!parseScene(scene, data))
		{
			return false;
		}

		return true;
	}

	//---------------------------------------------------------------------
	bool AssImpPlugin::executeExport (HlmsEditorPluginData* data)
	{
		// nothing to do
		return true;
	}

	//---------------------------------------------------------------------
	bool AssImpPlugin::parseScene (const aiScene* scene, HlmsEditorPluginData* data)
	{
		// The scene must have at least one model
		if (!scene->HasMeshes())
		{
			data->mOutErrorText = data->mInFileDialogName + " does not seem to contain a 3D model";
			return false;
		}

		// Interpret the model; only the first, if there are more models, just ignore them
		// TODO
		
		return true;
	}

}
