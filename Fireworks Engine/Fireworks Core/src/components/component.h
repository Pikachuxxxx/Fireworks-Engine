#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace fireworks { namespace components { 

	/// The list of components in the engine
	enum ComponentsList
	{
		RB2D = 0
	};

	/// To uniquely identify the component.
	struct ComponentType
	{
		std::string name;
		unsigned int typeID;
	};

	/// Class for creating components.
	class Component
	{
	public:
		/// Basic information about the type of the component.
		ComponentType componentType;
	protected:
		/// Creates the component.
		/// 
		/// Takes basic information to uniquely identify the component
		/// @param componentName The name of the component
		/// @param componentID The unique ID of the particular component
		Component(const std::string& componentName, unsigned int componentID);
		/// A Dummy method to make the class polymorphic
		virtual void Dummy() {}
	};

} }
