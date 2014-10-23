#include "GLSim/core/ModelLoader.h"
#include <istream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GL/glew.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

bool ModelLoader::loadMesh(const std::string& path, Mesh* mesh) const
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate); //| aiProcess_GenSmoothNormals); // | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);

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
		std::vector<GLfloat> verts;
		std::vector<GLushort> indices;
		std::vector<GLfloat> normals;

		for(unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
		{
			verts.push_back(scene->mMeshes[i]->mVertices[j].x);
			verts.push_back(scene->mMeshes[i]->mVertices[j].y);
			verts.push_back(scene->mMeshes[i]->mVertices[j].z);
		}

		for(unsigned int n = 0; n < scene->mMeshes[i]->mNumFaces; ++n)
		{
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[0]);
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[1]);
			indices.push_back(scene->mMeshes[i]->mFaces[n].mIndices[2]);
		}
		for(unsigned int n = 0; n < scene->mMeshes[i]->mNumVertices; ++n)
		{
			normals.push_back(scene->mMeshes[i]->mNormals[i].x);
			normals.push_back(scene->mMeshes[i]->mNormals[i].y);
			normals.push_back(scene->mMeshes[i]->mNormals[i].z);
		}
		mesh->setVertices(verts, indices, normals);
	}
}


/*const Mesh& ModelLoader::loadOBJ(const std::string& path) const
{
	Mesh& mesh = Mesh();
	//TODO: preallocate
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