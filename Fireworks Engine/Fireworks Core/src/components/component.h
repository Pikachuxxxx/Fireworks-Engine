#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace fireworks { namespace components { 

	enum Components
	{
		RB2D = 0
	};

	struct ComponentType
	{
		std::string name;
		unsigned int typeID;
	};

	class Component
	{
	public:
		ComponentType componentType;
	protected:
		Component(const std::string& componentName, unsigned int componentID);

		virtual void idk() {}

	};

} }
