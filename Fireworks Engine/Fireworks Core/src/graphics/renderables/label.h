#pragma once
#include <iostream>
#include <map>
#include <string>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "renderable2d.h"

#include "../../utils/glassert.h"

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

	/// The label class to render text onto the screen.
	class Label
	{
	public:
		/// The text of the label
		std::string							text;
		/// The position of the label
		maths::vec3							position;
		/// The color of the label
		maths::vec3							color;
		/// The font used to render the label
		Font								font;
	private:
		mutable std::map<char, Character>	m_Characters;
		Shader*								m_FontShader;
		unsigned int						m_VAO;
		unsigned int						m_VBO;
	public:
		/// Creates a new label to render text onto the screen.
		/// 
		/// @param text The text to render to the screen
		/// @param position The position on the screen where the Label will be places
		/// @param color The color of the Label
		/// @param font The font used to render the Label
		/// 
		/// @warning The position to render the text on the screen is in the limits X : (0, 800) and Y : (0, 600)
		/// This will be later updates to use the camera's orthogonal matrix to make things simpler
		Label(const char* text, maths::vec3 position, maths::vec3 color, Font& font);

		/// Renders the text onto the screen
		void renderText() const;
	private:
		void load();
	};

} }
