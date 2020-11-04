#include "component.h"

namespace fireworks { namespace components { 


	Component::Component(const std::string& componentName, unsigned int componentID)
	{
		componentType.name = componentName;
		componentType.typeID = componentID;
	}

	// Do not uncomment this
	/*template <typename T>
	void Component::AddComponent(T* component)
	{
		if (!dynamic_cast<Component> (T))
		{
			std::cerr << "ERROR::COMPONENT:: Not a valid component type" << std::endl;
			return;
		}
	}*/

} }

