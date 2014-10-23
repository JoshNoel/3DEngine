#ifndef OGL_MODELLOADER_INCLUDED
#define OGL_MODELLOADER_INCLUDED

#include "GLSim/core/Mesh.h"
#include <string>


namespace ogl { class ModelLoader; }
class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	
	//const Mesh& loadOBJ(const std::string& path) const;
	bool loadMesh(const std::string& path, Mesh* mesh) const;
};


#endif