/*

// Clear the previous map (if any)
		  // Clear the previous map (if any)
		ch_atlas.clear();

		// set the font size
		FT_Set_Pixel_Sizes(face, 0, 48);

		// initialize variables to keep track of texture atlas size
		int atlas_width = 0;
		int atlas_height = 0;

		// loop through the characters and load their glyphs
		for (unsigned char c = 0; c < 128; c++)
		{
			// load glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// update atlas size variables
			atlas_width += face->glyph->bitmap.width;
			atlas_height = std::max(atlas_height, static_cast<int>(face->glyph->bitmap.rows));
		}

		// generate texture for the atlas
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			atlas_width,
			atlas_height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			nullptr
		);

		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// initialize x position for next glyph
		int x = 0;

		// loop through the characters again and add their glyphs to the atlas
		for (unsigned char c = 0; c < 128; c++)
		{
			// load glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// add glyph to texture atlas
			glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				x,
				0,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// store glyph information in character map
			Character character = {
				textureID,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			ch_atlas.insert(std::pair<char, Character>(c, character));

			// update x position for next glyph
			x += face->glyph->bitmap.width;


		}

*/



/*

// Clear the previous map (if any)
		ch_atlas.clear();

		// set the font size
		FT_Set_Pixel_Sizes(face, 0, 48);

		// initialize variables to keep track of texture atlas size
		int atlas_width = 0;
		int atlas_height = 0;


		// loop through the characters and load their glyphs
		for (unsigned char c = 0; c < 128; c++)
		{
			// load glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// generate texture for glyph
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// update atlas size variables
			atlas_width += face->glyph->bitmap.width;
			atlas_height = std::max(atlas_height, static_cast<int>(face->glyph->bitmap.rows));


			// store character for later use
			Character character = {
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(unsigned int)face->glyph->advance.x,
				glm::vec2(0),
				glm::vec2(0),
				glm::vec2(0),
				glm::vec2(0)
			};
			ch_atlas.insert(std::pair<char, Character>(c, character));
		}

		// Update the texture dimensions
		TextureWidth = atlas_width;
		TextureHeight = atlas_height;

		// compute texture coordinates for each character
		float x = 0;
		float y = 0;
		for (auto& ch : ch_atlas)
		{
			Character& character = ch.second;

			// compute glyph texture coordinates
			character.top_left.x = x / atlas_width;
			character.top_left.y = y / atlas_height;
			character.bot_right.x = (x + character.Size.x) / atlas_width;
			character.bot_right.y = (y + character.Size.y) / atlas_height;

			// update x position for next glyph
			x += character.Size.x;
		}

		// compute normalized texture coordinates for whitespace character
		Character& space_char = ch_atlas[' '];
		space_char.top_left.x = 0.0f;
		space_char.top_left.y = 0.0f;
		space_char.bot_right.x = space_char.Size.x / atlas_width;
		space_char.bot_right.y = space_char.Size.y / atlas_height;

		// compute normalized texture coordinates for newline character
		Character& newline_char = ch_atlas['\n'];
		newline_char.top_left.x = 0.0f;
		newline_char.top_left.y = 0.0f;
		newline_char.bot_right.x = 0.0f;
		newline_char.bot_right.y = 0.0f;

*/




/*

		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// generate texture atlas
		// GLuint texture;
		glGenTextures(1, &label_textureID);
		glBindTexture(GL_TEXTURE_2D, label_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1024, 1024, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// initialize atlas variables
		int x = 0;
		int y = 0;
		int max_height = 0;

		// loop through all printable ASCII characters
		for (unsigned char c = 32; c < 128; c++)
		{
			// load character glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				continue;
			}

			// store character data in struct
			Character character =
			{
				0,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x,
				glm::vec4(x, y + face->glyph->bitmap.rows - face->glyph->bitmap_top,
					face->glyph->bitmap.width,
					-1.0f*face->glyph->bitmap.rows)
			};

			// add character to map
			ch_characters.insert(std::pair<char, Character>(c, character));

			// update atlas variables
			x += face->glyph->bitmap.width + 1;
			max_height = std::max(max_height, int(face->glyph->bitmap.rows));

			if (x >= 1024)
			{
				x = 0;
				y += max_height + 1;
				max_height = 0;
			}

			// update texture with glyph data
			glTexSubImage2D(GL_TEXTURE_2D,
				0,
				character.TextureCoords.x,
				character.TextureCoords.y,
				character.TextureCoords.z,
				character.TextureCoords.w,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);
		}


*/


/*


label_store::label_store()
	:label_char_list(), label_loc(0), text_color(0), text_angle(0.0f), font_size(0.0f), char_count(0)
{
	// Constructor
	// Stores individual line
}

label_store::~label_store()
{

}

void label_store::add_label(const char* label, glm::vec2 label_loc, float text_angle, float font_size)
{
	// Add the label
	unsigned int char_location = 0;

	for (const char* c = label; *c != '\0'; c++)
	{
		//Character ch;
		//ch.this_char = *c; // store the character
		//ch.texture_id =0; // Set texture id 0
		//ch.char_location = char_location;
		label_char_list.insert(std::make_pair(char_location, *c));

		// Iterate the location
		char_location++;
	}

	this->char_count = char_location;
	this->label_loc = label_loc;
	this->text_angle = text_angle;
	this->font_size = font_size;
}

void label_store::get_buffer(float* label_vertices, unsigned int* label_indices,
	unsigned int& label_vertices_count, unsigned int& label_indices_count, std::map<char, Character>& char_atlas)
{
	float x_val = label_loc.x;
	float y_val = label_loc.y;

	// return the buffer of each character (<> font size = 0.04f, <> font gap = 0.01f)
	for (auto& char_s : label_char_list)
	{

		Character ch = char_atlas[char_s.second];
		font_size = 0.002f;

		float xpos = x_val + (ch.Bearing.x * font_size);
		float ypos = y_val - (ch.Size.y - ch.Bearing.y) * font_size;

		float w = ch.Size.x * font_size;
		float h = ch.Size.y * font_size;

		glm::vec4 texture_scaled = ch.TextureCoords / font_size;

		// X Y coordinates
		// Point 1
		// Vertices [0,0] // 0th point
		label_vertices[label_vertices_count + 0] = xpos;
		label_vertices[label_vertices_count + 1] = ypos + h;

		// Label origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = texture_scaled.x;
		label_vertices[label_vertices_count + 5] = texture_scaled.y;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 2
		// Vertices [0,1] // 1th point
		label_vertices[label_vertices_count + 0] = xpos;
		label_vertices[label_vertices_count + 1] = ypos;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = texture_scaled.x;
		label_vertices[label_vertices_count + 5] = texture_scaled.y + texture_scaled.w;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 3
		// Vertices [1,1] // 3th point
		label_vertices[label_vertices_count + 0] = xpos + w;
		label_vertices[label_vertices_count + 1] = ypos;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = texture_scaled.x + texture_scaled.z;
		label_vertices[label_vertices_count + 5] = texture_scaled.y + texture_scaled.w;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 4
		// Vertices [1,0] // 4th point
		label_vertices[label_vertices_count + 0] = xpos + w;
		label_vertices[label_vertices_count + 1] = ypos + h;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = texture_scaled.x + texture_scaled.z;
		label_vertices[label_vertices_count + 5] = texture_scaled.y;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		x_val += (ch.Advance >> 6) * font_size;

		//__________________________________________________________________________________________

		// Fix the index buffers
		// Set the node indices
		unsigned int t_id = ((label_indices_count / 6) * 4);
		// Triangle 0,1,2
		label_indices[label_indices_count + 0] = t_id + 0;
		label_indices[label_indices_count + 1] = t_id + 1;
		label_indices[label_indices_count + 2] = t_id + 2;

		// Triangle 2,3,0
		label_indices[label_indices_count + 3] = t_id + 2;
		label_indices[label_indices_count + 4] = t_id + 3;
		label_indices[label_indices_count + 5] = t_id + 0;

		// Increment
		label_indices_count = label_indices_count + 6;
	}
}


void label_store::get_buffer1(float* label_vertices, unsigned int* label_indices,
	unsigned int& label_vertices_count, unsigned int& label_indices_count, std::map<char, Character>& char_atlas)
{
	//const float char_gap = font_size * 0.25f;
	//glm::vec2 temp_pt;
	//glm::vec2 char_pt;
	float x_val = label_loc.x;
	float y_val = label_loc.y;

	// return the buffer of each character (<> font size = 0.04f, <> font gap = 0.01f)
	for (auto& char_s : label_char_list)
	{

		Character ch = char_atlas[char_s.second];
		font_size =0.002f;

		float xpos = x_val +(ch.Bearing.x * font_size);
		float ypos = y_val -(ch.Size.y - ch.Bearing.y) * font_size;

		float w = ch.Size.x *font_size;
		float h = ch.Size.y *font_size;


		// X Y coordinates
		// Point 1
		// Vertices [0,0] // 0th point
		label_vertices[label_vertices_count + 0] = xpos;
		label_vertices[label_vertices_count + 1] = ypos+h;

		// Label origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = 0;
		label_vertices[label_vertices_count + 5] = 0;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 2
		// Vertices [0,1] // 1th point
		label_vertices[label_vertices_count + 0] = xpos;
		label_vertices[label_vertices_count + 1] = ypos;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = 0;
		label_vertices[label_vertices_count + 5] = 1;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 3
		// Vertices [1,1] // 3th point
		label_vertices[label_vertices_count + 0] = xpos+w;
		label_vertices[label_vertices_count + 1] = ypos;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = 1;
		label_vertices[label_vertices_count + 5] = 1;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		//__________________________________________________________________________________________
		// Point 4
		// Vertices [1,0] // 4th point
		label_vertices[label_vertices_count + 0] = xpos+w;
		label_vertices[label_vertices_count + 1] = ypos+h;

		// Font origin
		label_vertices[label_vertices_count + 2] = label_loc.x;
		label_vertices[label_vertices_count + 3] = label_loc.y;

		// Texture Glyph coordinate
		label_vertices[label_vertices_count + 4] = 1;
		label_vertices[label_vertices_count + 5] = 0;

		// Iterate
		label_vertices_count = label_vertices_count + 6;

		x_val += (ch.Advance >> 6) * font_size;

		//__________________________________________________________________________________________

		// Fix the index buffers
		// Set the node indices
		unsigned int t_id = ((label_indices_count / 6) * 4);
		// Triangle 0,1,2
		label_indices[label_indices_count + 0] = t_id + 0;
		label_indices[label_indices_count + 1] = t_id + 1;
		label_indices[label_indices_count + 2] = t_id + 2;

		// Triangle 2,3,0
		label_indices[label_indices_count + 3] = t_id + 2;
		label_indices[label_indices_count + 4] = t_id + 3;
		label_indices[label_indices_count + 5] = t_id + 0;

		// Increment
		label_indices_count = label_indices_count + 6;
	}
}

glm::vec2 label_store::rotate_pt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle)
{
	// Return the rotation point
	glm::vec2 translated_pt = pt - rotate_about;

	// Apply rotation
	float radians = (rotation_angle);// * 3.14159365f) / 180.0f; // convert degrees to radians
	float cos_theta = cos(radians);
	float sin_theta = sin(radians);

	// Rotated point of the corners
	glm::vec2 rotated_pt = glm::vec2((translated_pt.x * cos_theta) - (translated_pt.y * sin_theta),
		(translated_pt.x * sin_theta) + (translated_pt.y * cos_theta));

	return (rotated_pt + rotate_about);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



*/