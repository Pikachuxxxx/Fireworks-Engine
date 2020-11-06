#pragma once
#include <iostream>
#include <map>
#include <string>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "renderable2d.h"

namespace fireworks { namespace graphics {

	struct Character
	{
		unsigned int	TextureID;
		maths::vec2		Size;
		maths::vec2		Bearing;
		unsigned int	Advance;
	};

	struct Font
	{
		const char*		fontPath;
		unsigned int	fontSize;

		Font(const char* path, unsigned int size)
		{
			this->fontPath = path;
			this->fontSize = size;
		}
	};

	class Label
	{
	public:
		std::string							text;
		maths::vec3							position;
		maths::vec3							color;
		Font								font;
	private:
		mutable std::map<char, Character>	m_Characters;
		Shader*								m_FontShader;
		unsigned int						m_VAO;
		unsigned int						m_VBO;
	public:
		Label(const char* text, maths::vec3 position, maths::vec3 color, Font& font);

		void renderText() const;
	private:
		void load();
	};

} }
