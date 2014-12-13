#include "GLSim/core/ModelLoader.h"
#include <istream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GL/glew.h"
#include "fbxsdk.h"


ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

using namespace fbxsdk_2015_1;
bool ModelLoader::loadMesh(const std::string& path, Mesh* obj) const
{
	FbxManager* fbxManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(fbxManager, "");

	if(!importer->Initialize(path.c_str(), -1, fbxManager->GetIOSettings()))
	{
		fprintf(stdout, "Failed Intializing fbx importer\n");
		fprintf(stdout, "FBX Error: %s\n\n", importer->GetStatus().GetErrorString());
	}

	FbxScene* scene = FbxScene::Create(fbxManager, "Scene");
	importer->Import(scene);
	importer->Destroy();
	FbxGeometryConverter converter(fbxManager);
	converter.Triangulate(scene, false);
	FbxNode* root = scene->GetRootNode();

	if(root)
	{
		std::vector<Vertex> vertices;
		std::vector<GLushort> indices;
		int numChild = root->GetChildCount();
		for(unsigned int x = 0; x < numChild; ++x)
		{
			FbxNode* Object = root->GetChild(x);
			FbxMesh* mesh = Object->GetMesh();
			//if(mesh->GenerateNormals(true))
				//printf("generated normals....");
			indices.resize(mesh->GetPolygonVertexCount());
			vertices.resize(mesh->GetPolygonVertexCount());
			if(mesh != nullptr)
			{
				FbxVector4* controlPoints = mesh->GetControlPoints();
				int loops = 0;
				for(unsigned int i = 0; i < mesh->GetPolygonCount(); ++i)
				{
					int index = 0;
					for(unsigned int j = 0; j < 3; ++j)
					{
						FbxVector4 normal;
						index = mesh->GetPolygonVertex(i, j);
						indices[loops] = loops;
						vertices[loops].position.x = static_cast<float>(controlPoints[index][0]);
						vertices[loops].position.y = static_cast<float>(controlPoints[index][1]);
						vertices[loops].position.z = static_cast<float>(controlPoints[index][2]);
					
						if(!mesh->GetPolygonVertexNormal(i, j, normal))
							printf("error getting normals\n");

						vertices[loops].normal.x += static_cast<float>(normal[0]);
						vertices[loops].normal.y += static_cast<float>(normal[1]);
						vertices[loops].normal.z += static_cast<float>(normal[2]);

						if(!obj->unmapped)
						{
							FbxStringList UVSetNameList;
							FbxVector2 uv;
							bool unmapped;
							mesh->GetUVSetNames(UVSetNameList);
							if(UVSetNameList[0])
							{
								if(!mesh->GetPolygonVertexUV(i, j, UVSetNameList[0], uv, unmapped))
									printf("error getting uvs\n");
								if(!unmapped)
								{
									vertices[loops].uv.x += static_cast<float>(uv[0]);
									vertices[loops].uv.y += static_cast<float>(uv[1]);
								}
								else
									obj->unmapped = true;
							}
						}
						/*
						//If normal at index is different than new normal add a new vertex to array
						if(vertices[index].normal.x != normal[0] || vertices[index].normal.y != normal[1] || vertices[index].normal.x != normal[2])
						{
							//if unitialized add at index
							if(vertices[index].normal == glm::vec3())
							{
								vertices[index].normal.x += static_cast<float>(normal[0]);
								vertices[index].normal.y += static_cast<float>(normal[1]);
								vertices[index].normal.z += static_cast<float>(normal[2]);
							}
							vertices[index].normal.x += static_cast<float>(normal[0]);
							vertices[index].normal.y += static_cast<float>(normal[1]);
							vertices[index].normal.z += static_cast<float>(normal[2]);
						}*/
						/*
						FbxStringList UVSetNameList;
						FbxVector2 uv;
						bool unmapped;
						mesh->GetUVSetNames(UVSetNameList);
						if(UVSetNameList[0] != nullptr)
						{
							if(!mesh->GetPolygonVertexUV(i, j, UVSetNameList[0], uv, unmapped))
								printf("error getting uvs\n");
							vertices[index].uv.x += static_cast<float>(uv[0]);
							vertices[index].uv.y += static_cast<float>(uv[1]);
						}*/

						loops++;
					}
				}
			}
		}
		/*
		for(unsigned int i = 0; i < vertices.size(); ++i)
		{
			vertices[i].normal = glm::normalize(vertices[i].normal);
		}
		for(unsigned int i = 0; i < vertices.size(); ++i)
		{
			vertices[i].uv = glm::normalize(vertices[i].uv);
		}*/
		obj->setVertices(vertices, indices);
		scene->Destroy();
		ios->Destroy();
		fbxManager->Destroy();
		return true;
	}
	scene->Destroy();
	ios->Destroy();
	fbxManager->Destroy();
	return false;	
}

/*
bool ModelLoader::loadMesh(const std::string& path, Mesh* mesh) const
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals); // | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);

	if(!scene)
	{
		fprintf(stdout, "Error parsing mesh at: %s\n", path);
		return false;
	}
	
	if(scene->mNumMeshes > 1)
	{
		fprintf(stdout, "Error parsing mesh at: %s\n Too many meshes. Only 1 allowed.\n", path);
		return false;
	}

	for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		std::vector<Vertex> verts;
		std::vector<GLushort> indices;

		for(unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
		{
			aiVector3D pos = scene->mMeshes[i]->mVertices[j];
			aiVector3D norm = scene->mMeshes[i]->mNormals[i];
			verts.push_back(Vertex(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(norm.x, norm.y, norm.z)));
		}

		for(unsigned int n = 0; n < scene->mMeshes[i]->mNumFaces; ++n)
		{
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[0]);
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[1]);
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[2]);
		}
		mesh->setVertices(verts, indices);
	}
	return true;
}
*/

/*const Mesh& ModelLoader::loadOBJ(const std::string& path) const
{
	Mesh& mesh = Mesh();
	//todo: preallocate
	std::vector<GLfloat> vertices;
	std::vector<GLushort> indices;

	size_t pos = path.find_last_of('.');
	if(pos == path.npos)
	{
		fprintf(stdout, "Error loading OBJ file at: %s\n", path.c_str());
		return mesh;
	}

	std::string ext;
	for(int i = pos + 1; i < path.size(); ++i)
	{
		ext += path[i];
	}

	if(ext != "obj")
	{
		fprintf(stdout, "Error loading OBJ file at: %s\n Files of type '%s' are not allowed", path.c_str(), ext);
		return mesh;
	}

	std::ifstream stream;
	stream.open(path);
	std::string line;
	while(std::getline(stream, line))
	{		
		if(stream.eof())
			break;
		std::stringstream strStream(line);

		std::string id;
		strStream >> id;
		if(id == "#")
			continue;
		else if(id == "v")
		{
			std::string v = "";
			while(strStream >> v)
			{
				if(v == " " || v == "v")
					strStream >> v;

				vertices.push_back(std::stof(v));
			}
			continue;
		}
		else if(id == "f")
		{
			std::string f = "";
			while(strStream >> f)
			{
				if(f == " " || f == "f")
					strStream >> f;

				indices.push_back(std::stoi(f)-1);
			}
			continue;
		}
	
	}

	mesh.setVertices(vertices, indices);
	return mesh;
}*/