#ifndef OGL_OBJECT_INCLUDED
#define OGL_OBJECT_INCLUDED

#include <unordered_map>
#include <memory>
#include "GLSim/core/Component.h"
#include "GLSim/core/Transform.h"
#include "GLSim/core/RenderMesh.h"
#include "GLSim/core/Camera.h"
#include "GLSim/core/GlobalSettings.h"
#include "GLSim/core/Light.h"


namespace ogl { class Object; }
class Object
{
public:
	Object(const std::string& name = "", const std::string& tag = ogl::tags.at((int)ogl::DEFAULT_TAGS::TAG_DEFAULT));
	virtual ~Object();

	void addComponent(Component*);

	//todo: use enableIf
	template<typename T>
	T* getComponent()
	{
		Component::COMPONENT_TYPE type = (Component::COMPONENT_TYPE)-1;

		if(std::is_same<T, RenderMesh>::value)
			type = Component::COMPONENT_TYPE::RENDER_MESH;
		else if(std::is_same<T, Transform>::value)
			type = Component::COMPONENT_TYPE::TRANSFORM;
		else if (std::is_same<T, Camera>::value)
			type = Component::COMPONENT_TYPE::CAMERA;
		else if (std::is_same<T, Light>::value)
			type = Component::COMPONENT_TYPE::LIGHT;

		if(m_compMap.find(type) == m_compMap.end())
			return nullptr;
		
		return static_cast<T*>(m_compMap.at(type));
	}

	inline std::string& getName() { return m_name; }
	inline std::string& getTag() { return m_tag; }

private:
	std::unordered_map<Component::COMPONENT_TYPE, Component*> m_compMap;
	std::string m_name;
	std::string m_tag;


};
#endif
