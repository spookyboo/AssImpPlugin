/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

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
#ifndef __XmlSerializer_H__
#define __XmlSerializer_H__

#include "XML/tinyxml.h"
#include "hlms_editor_plugin.h"
#include <assimp/scene.h>

namespace Ogre
{
	// Default is generate V2 meshes for desktop. Set USE_MESHTOOL_CMD to a different command string 
	// for other mesh platforms
	static const String MESHTOOL_CMD_DESKTOP_WITH_NORMALS = "OgreMeshTool -v2 -e -t -ts 4 -O puqs ";
	static String MESHTOOL_CMD = MESHTOOL_CMD_DESKTOP_WITH_NORMALS;

	/** Plugin instance for AssImpPlugin */
	class XmlSerializer
	{
	public:
		XmlSerializer(void);
		virtual ~XmlSerializer(void);

		/* Read the assimp scene and convert the mesh data to an xml file (and save it)
		 * The basename of the file is the same as the basename of the imported file
		 * E.g. If the loaded file is mymodel.fbx, the xml is called mymodel.xml
		 */
		bool convertAssImpMeshToXml(const aiScene* scene, 
			const String& fileNameXml,
			HlmsEditorPluginData* data);

		/* Interpret an xml file and use Ogre's build-in XMLMeshSerializer to convert to a V2 mesh
		 */
		bool convertXmlFileToMesh(const String& xmlFileName, 
			const String& meshFileName,
			HlmsEditorPluginData* data);

		/* Read an Ogre mesh xml file and check to see wheter it is an Ogre mesh xml file
		 */
		bool importOgreMeshXml(const String& xmlFileName, HlmsEditorPluginData* data);

	protected:
		// Level 2 elements
		bool writeSharedGeometry(const String& sharedGeometryId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		bool writeSubMeshes(const String& submMeshesId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);
		
		bool writeSkeletonLink(const String& skeletonlinkId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);
		
		bool writeLodInfo(const String& lodInfoId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		bool writeSubMeshNames(const String& subMeshNamesId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		bool writeExtremes(const String& extremesId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		bool writePoses(const String& posesId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		bool writeAnimations(const String& animationsId,
			TiXmlElement* root,
			const aiScene* scene,
			HlmsEditorPluginData* data);

		// level 3 elements
		bool writeSubMesh(const String& submMeshId,
			TiXmlElement* subMeshNode,
			const aiMesh* subMesh,
			HlmsEditorPluginData* data);

		// level 4 elements
		bool writeFaces(const String& faceId,
			TiXmlElement* facesNode,
			const aiMesh* subMesh,
			HlmsEditorPluginData* data);

		bool writeVertexBoneAssignments(const String& vertexBoneAssignmentsId,
			TiXmlElement* boneAssignmentsNode,
			const aiMesh* subMesh,
			HlmsEditorPluginData* data);

		// level 4 elements
		bool writeVertices(const String& vertexBufferId,
			TiXmlElement* vertexBufferNode,
			const aiMesh* subMesh,
			HlmsEditorPluginData* data);
	};
}

#endif
