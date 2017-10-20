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

#include "Ogre.h"
#include "XmlMeshSerializer.h"

namespace Ogre
{
	//---------------------------------------------------------------------
	XmlSerializer::XmlSerializer(void)
	{
	}

	//---------------------------------------------------------------------
	XmlSerializer::~XmlSerializer(void)
	{
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::importOgreMeshXml(const String& xmlFileName, HlmsEditorPluginData* data)
	{
		LogManager::getSingleton().logMessage("XmlSerializer::importOgreMeshXml " + xmlFileName + "...");
		TiXmlDocument xmlDocument (xmlFileName);
		xmlDocument.LoadFile();
		if (xmlDocument.Error())
		{
			data->mOutErrorText = xmlDocument.ErrorDesc();
			return false;
		}
		TiXmlElement* root = xmlDocument.RootElement();
		String rootValue(root->Value());
		LogManager::getSingleton().logMessage("XmlSerializer::importOgreMeshXml root" + rootValue + "...");
		if (rootValue != "mesh")
		{
			data->mOutErrorText = "The xml file is not an Ogre mesh xml file";
			return false;
		}

		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::convertAssImpMeshToXml(const aiScene* scene, 
		const String& fileNameXml, 
		HlmsEditorPluginData* data)
	{
		// All meshes in the scene become submeshes in Ogre
		TiXmlDocument xmlDocument;

		// root node
		TiXmlElement* root = new TiXmlElement("mesh");
		xmlDocument.LinkEndChild(root);
		
		// shared geometry
		if (!writeSharedGeometry("sharedgeometry", root, scene, data))
			return false;

		// submeshes
		if (!writeSubMeshes("submeshes", root, scene, data))
			return false;

		// skeleton link
		if (!writeSkeletonLink("skeletonlink", root, scene, data))
			return false;

		//Lod
		if (!writeLodInfo("levelofdetail", root, scene, data))
			return false;

		// submesh names
		if (!writeSubMeshNames("submeshnames", root, scene, data))
			return false;

		// submesh extremes
		if (!writeExtremes("extremes", root, scene, data))
			return false;

		// poses
		if (!writePoses("poses", root, scene, data))
			return false;

		// animations
		if (!writeAnimations("animations", root, scene, data))
			return false;

		//String fileName = data->mInImportPath + data->mInFileDialogBaseName + ".xml";
		xmlDocument.SaveFile(fileNameXml);
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeSharedGeometry(const String& sharedGeometryId,
		TiXmlElement* root,
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeSubMeshes (const String& submMeshesId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		if (!scene->HasMeshes())
		{
			data->mOutErrorText = "The loaded model does not have any (sub)meshes";
			return false;
		}

		TiXmlElement* subMeshesNode;
		subMeshesNode = new TiXmlElement(submMeshesId);
		root->LinkEndChild(subMeshesNode);

		// SubMeshes
		unsigned int meshCount = 0;
		while (meshCount < scene->mNumMeshes)
		{
			// Add 'n' number of submesh elements
			TiXmlElement* subMeshNode = new TiXmlElement("submesh");
			subMeshesNode->LinkEndChild(subMeshNode);
			if (!writeSubMesh("submesh", subMeshNode, scene->mMeshes[meshCount], data))
				return false;

			++meshCount;
		}

		return true;
	}


	//---------------------------------------------------------------------
	bool XmlSerializer::writeSkeletonLink (const String& skeletonlinkId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeLodInfo (const String& lodInfoId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeSubMeshNames (const String& subMeshNamesId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		/*
		if (scene->HasMeshes())
		{
			TiXmlElement* subMeshNamesNode = new TiXmlElement(subMeshNamesId);
			root->LinkEndChild(subMeshNamesNode);
		}
		*/
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeExtremes (const String& extremesId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writePoses (const String& posesId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeAnimations (const String& animationsId,
		TiXmlElement* root, 
		const aiScene* scene,
		HlmsEditorPluginData* data)
	{
		/*
		if (scene->HasAnimations())
		{
			TiXmlElement* animationsNode = new TiXmlElement(animationsId);
			root->LinkEndChild(animationsNode);
		}
		*/
		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeSubMesh(const String& submMeshId,
		TiXmlElement* subMeshNode,
		const aiMesh* subMesh,
		HlmsEditorPluginData* data)
	{
		subMeshNode->SetAttribute("material", "BaseWhite");
		subMeshNode->SetAttribute("usesharedvertices", "false");
		subMeshNode->SetAttribute("use32bitindexes", "false");
		subMeshNode->SetAttribute("operationtype", "triangle_list");
		TiXmlElement* facesNode;
		TiXmlElement* geometryNode;
		TiXmlElement* vertexBufferNode;
		TiXmlElement* boneAssignmentsNode;

		// Faces
		if (subMesh->HasFaces())
		{
			if (subMesh->mFaces->mNumIndices != 3)
			{
				data->mOutErrorText = "Error; only models with triangle lists are supported";
				return false;
			}

			facesNode = new TiXmlElement("faces");
			facesNode->SetAttribute("count", subMesh->mNumFaces);
			subMeshNode->LinkEndChild(facesNode);

			// Write all faces
			if (!writeFaces("face", facesNode, subMesh, data))
				return false;
		}

		// Geometry
		if (subMesh->HasPositions())
		{
			geometryNode = new TiXmlElement("geometry");
			geometryNode->SetAttribute("vertexcount", subMesh->mNumVertices);
			subMeshNode->LinkEndChild(geometryNode);
			vertexBufferNode = new TiXmlElement("vertexbuffer");
			vertexBufferNode->SetAttribute("positions", "true");
			geometryNode->LinkEndChild(vertexBufferNode);

			if (subMesh->HasNormals())
				vertexBufferNode->SetAttribute("normals", "true");
			else
				vertexBufferNode->SetAttribute("normals", "false");
			
			vertexBufferNode->SetAttribute("texture_coord_dimensions_0", "float2"); // TODO: Extend

			if (subMesh->HasTangentsAndBitangents())
				vertexBufferNode->SetAttribute("tangents", "true");
			else
				vertexBufferNode->SetAttribute("tangents", "false");

			if (subMesh->HasTextureCoords(0))
			{
				vertexBufferNode->SetAttribute("texture_coords", "1"); // TODO: Extend with mulitple texture coordinate sets
			}
			
			// Write all vertices, normals and tex coords
			if (!writeVertices("vertex", vertexBufferNode, subMesh, data))
				return false;
		}

		// TODO
		// The code to create the bones is not correct. Vertex indices and bone indices 
		// do not match with xml output of the Ogre Mesh XML Serializer.
		/*
		if (subMesh->HasBones())
		{
			boneAssignmentsNode = new TiXmlElement("boneassignments");
			subMeshNode->LinkEndChild(boneAssignmentsNode);
			if (!writeVertexBoneAssignments("vertexboneassignment", boneAssignmentsNode, subMesh, data))
				return false;
		}
		*/

		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeFaces(const String& faceId,
		TiXmlElement* facesNode,
		const aiMesh* subMesh,
		HlmsEditorPluginData* data)
	{
		unsigned int faceCount = 0;
		aiFace* face;
		TiXmlElement* faceNode;
		while (faceCount < subMesh->mNumFaces)
		{
			// Add 'x' number of face elements
			face = &subMesh->mFaces[faceCount];
			unsigned int indexCount = 0;
			faceNode = new TiXmlElement("face");
			facesNode->LinkEndChild(faceNode);
			while (indexCount < face->mNumIndices)
			{
				faceNode->SetAttribute("v" + StringConverter::toString(indexCount + 1), face->mIndices[indexCount]);
				++indexCount;
			}

			++faceCount;
		}

		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeVertices(const String& vertexBufferId,
		TiXmlElement* vertexBufferNode,
		const aiMesh* subMesh,
		HlmsEditorPluginData* data)
	{
		unsigned int vertexCount = 0;
		aiVector3D* vertex;
		aiVector3D* normal;
		aiVector3D* tangent;
		aiVector3D* texCoord;
		TiXmlElement* vertexNode;
		TiXmlElement* positionNode;
		TiXmlElement* normalNode;
		TiXmlElement* tangentNode;
		TiXmlElement* texCoordNode;

		// Add 'x' number of vertex elements, normalsm texture coords and tangents
		while (vertexCount < subMesh->mNumVertices)
		{
			vertexNode = new TiXmlElement(vertexBufferId);
			vertexBufferNode->LinkEndChild(vertexNode);

			// Position
			positionNode = new TiXmlElement("position");
			vertex = &subMesh->mVertices[vertexCount];
			positionNode->SetAttribute("x", StringConverter::toString(vertex->x));
			positionNode->SetAttribute("y", StringConverter::toString(vertex->y));
			positionNode->SetAttribute("z", StringConverter::toString(vertex->z));
			vertexNode->LinkEndChild(positionNode);

			// Normal
			if (subMesh->HasNormals())
			{
				normalNode = new TiXmlElement("normal");
				normal = &subMesh->mNormals[vertexCount];
				normalNode->SetAttribute("x", StringConverter::toString(normal->x));
				normalNode->SetAttribute("y", StringConverter::toString(normal->y));
				normalNode->SetAttribute("z", StringConverter::toString(normal->z));
				vertexNode->LinkEndChild(normalNode);
			}

			// Tangent
			if (subMesh->HasTangentsAndBitangents())
			{
				tangentNode = new TiXmlElement("tangent");
				tangent = &subMesh->mTangents[vertexCount];
				tangentNode->SetAttribute("x", StringConverter::toString(tangent->x));
				tangentNode->SetAttribute("y", StringConverter::toString(tangent->y));
				tangentNode->SetAttribute("z", StringConverter::toString(tangent->z));
				vertexNode->LinkEndChild(tangentNode);
			}

			// Texture coordinates (TODO: Currently only one set)
			if (subMesh->HasTextureCoords(0))
			{
				texCoordNode = new TiXmlElement("texcoord");
				texCoord = &subMesh->mTextureCoords[0][vertexCount];
				texCoordNode->SetAttribute("u", StringConverter::toString(texCoord->x));
				texCoordNode->SetAttribute("v", StringConverter::toString(texCoord->y));
				vertexNode->LinkEndChild(texCoordNode);
			}

			++vertexCount;
		}

		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::writeVertexBoneAssignments(const String& vertexBoneAssignmentsId,
		TiXmlElement* boneAssignmentsNode,
		const aiMesh* subMesh,
		HlmsEditorPluginData* data)
	{
		aiBone* bone;
		TiXmlElement* vertexBoneAssignmentNode;
		float weight;
		struct BoneAssignmentStruct
		{
			unsigned int vertexIndex;
			unsigned int boneIndex;
			float weight;
		};

		std::multimap<int, BoneAssignmentStruct> boneAssignmentMmap;
		unsigned int totalNumWeights = 0;
		BoneAssignmentStruct boneAssignmentStruct;
		unsigned int boneCount = 0;
		unsigned int weightCount = 0;
		unsigned int substract = 0;
		while (boneCount < subMesh->mNumBones)
		{
			bone = subMesh->mBones[boneCount];
			weightCount = 0;
			while (weightCount < bone->mNumWeights)
			{
				weight = bone->mWeights[weightCount].mWeight;
				if (weight != 0.0f)
				{
				
					boneAssignmentStruct.vertexIndex = bone->mWeights[weightCount].mVertexId - substract;
					boneAssignmentStruct.boneIndex = boneCount;
					boneAssignmentStruct.weight = weight;
					boneAssignmentMmap.insert(std::make_pair(boneAssignmentStruct.vertexIndex, boneAssignmentStruct));
				}
				
				++weightCount;
			}
			
			++boneCount;
		}

		std::multimap<int, BoneAssignmentStruct>::const_iterator it = boneAssignmentMmap.begin();
		std::multimap<int, BoneAssignmentStruct>::const_iterator itEnd = boneAssignmentMmap.end();
		unsigned int vertexIndex = 0;
		while (it != itEnd)
		{
			boneAssignmentStruct = it->second;
			vertexBoneAssignmentNode = new TiXmlElement(vertexBoneAssignmentsId);
			boneAssignmentsNode->LinkEndChild(vertexBoneAssignmentNode);
			vertexBoneAssignmentNode->SetAttribute("vertexindex", StringConverter::toString(boneAssignmentStruct.vertexIndex));
			vertexBoneAssignmentNode->SetAttribute("boneindex", StringConverter::toString(boneAssignmentStruct.boneIndex));
			vertexBoneAssignmentNode->SetAttribute("weight", StringConverter::toString(boneAssignmentStruct.weight));
			++it;
			++vertexIndex;
		}

		return true;
	}

	//---------------------------------------------------------------------
	bool XmlSerializer::convertXmlFileToMesh(const String& xmlFileName, 
		const String& meshFileName,
		HlmsEditorPluginData* data)
	{
		std::string meshToolCmd = "OgreMeshTool -v2 ";
		std::string meshToolGenerateTangents = "";
		std::string meshToolGenerateEdgeLists = "-e ";
		std::string meshToolOptimize = "-O qs ";

		// First get the property values (from the HLMS Editor)
		std::map<std::string, Ogre::HlmsEditorPluginData::PLUGIN_PROPERTY> properties = data->mInPropertiesMap;
		std::map<std::string, Ogre::HlmsEditorPluginData::PLUGIN_PROPERTY>::iterator it = properties.find("generate_edge_lists");
		if (it != properties.end() && (it->second).boolValue)
			meshToolGenerateEdgeLists = "";

		it = properties.find("generate_tangents");
		if (it != properties.end() && (it->second).boolValue)
			meshToolGenerateTangents = "-t -ts 4 ";

		it = properties.find("optimize_for_desktop");
		if (it != properties.end() && (it->second).boolValue)
			meshToolOptimize = "-O puqs ";

		meshToolCmd += meshToolGenerateEdgeLists + meshToolGenerateTangents + meshToolOptimize;

		std::string runOgreMeshTool = meshToolCmd + "\"" + xmlFileName + "\" \"" + meshFileName + "\"";
		LogManager::getSingleton().logMessage("XmlSerializer::convertXmlFileToMesh executing: " + runOgreMeshTool + "...");
		system(runOgreMeshTool.c_str());
		return true;
	}
}
