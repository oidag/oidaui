#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <oidaui/oidaui.h>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include "font.hpp"
#include "../util/shader.hpp"
#include "../errors.h"
#include "../locale.h"

using namespace Font;

FT_Library ft = 0;

struct Font::character {
	unsigned int textId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	glm::ivec2 advance;
};

util::Shader *glyphShader;

//todo: https://learnopengl.com/In-Practice/Text-Rendering
oui_err Font::TypeFace::load(const char *path, struct oui_typeface_config c) {

	this->config = c;

	FT_Face face;

	if (FT_New_Face(ft, path, 0, &face)) {
		return OUI_EUNKNOWN;
	}

	FT_Set_Pixel_Sizes(face, this->config.pixelWidth, this->config.pixelHeight);

	this->characterc = this->config.charCodeLen;
	this->characterv = (struct character*)realloc(this->characterv
			, this->characterc * sizeof(struct character));

	// disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	const unsigned int codeStart = config.charCodeStart;
	const unsigned int codeEnd = config.charCodeStart + config.charCodeLen;
	for (unsigned int c = codeStart; c < codeEnd; c++) {

		// load the glyph
		if (int errc = FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			log_errorf(_("failed to load character code %d: Error %d - %s")
					   , c
					   , errc
					   , FT_Error_String(errc));
			free(this->characterv);
			FT_Done_Face(face);
			return OUI_ECRITICAL;
		}

		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				int(face->glyph->bitmap.width),
				int(face->glyph->bitmap.rows),
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

		// add to character map
		struct Font::character character = {
				.textId = texture,
				.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				.advance = glm::ivec2(face->glyph->advance.x, face->glyph->advance.y),
		};
		this->characterv[c - codeStart] = character;
	}

	// free up the resources
	FT_Done_Face(face);

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return OUI_ENONE;
}

TypeFace::TypeFace() {}

TypeFace::~TypeFace() {
	if(this->characterv) {
		free(this->characterv);
	}
}

oui_font_measurement TypeFace::size(const wchar_t *text) {
	unsigned int textlen = wcslen(text);
	if(!textlen) return {0};

	// iterate through all characters
	const unsigned int codeStart = this->config.charCodeStart;
	const unsigned int codeEnd = this->config.charCodeStart + this->config.charCodeLen;
	oui_font_measurement ret = {0};

	for (unsigned int c = 0; c < textlen; c++) {

		wchar_t charcode = text[c];
		if (charcode >= codeEnd || charcode < codeStart) {
			log_errorf(
					_("cannot calculate character %d - out of range of loaded characters [%d:%d)"),
					charcode, codeStart, codeEnd);
			continue;
		}
		struct character ch = characterv[charcode - codeStart];

		if ( ch.bearing.y > ret.baselineAbove) {
			ret.baselineAbove = ch.bearing.y;
		}

		int subBearing = ch.size.y - ch.bearing.y;
		if(subBearing > ret.baselineBelow) {
			ret.baselineBelow = subBearing;
		}

		ret.width += int(ch.advance.x >> 6);
	}

	ret.height = ret.baselineBelow + ret.baselineAbove;
	return ret;
}


void Font::TypeFace::render(const wchar_t *text, float x, float y, glm::vec3 color) {
	glyphShader->use();
	glUniform3f(glGetUniformLocation(glyphShader->ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	unsigned int textlen = wcslen(text);
	const unsigned int codeStart = this->config.charCodeStart;
	const unsigned int codeEnd = this->config.charCodeStart + this->config.charCodeLen;
	for (unsigned int c = 0; c < textlen; c++) {

		wchar_t charcode = text[c];
		if(charcode >= codeEnd || charcode < codeStart) {
			log_errorf(_("cannot write character %d - out of range of loaded characters [%d:%d)")
					   , charcode
					   , codeStart
					   , codeEnd);
			continue;
		}
		struct character ch = characterv[charcode - codeStart];

		float xpos = x + ch.bearing.x;
		float ypos = y - ch.bearing.y;
		float w = ch.size.x;
		float h = ch.size.y;

		// update VBO for each character
		float vertices[6][4] = {
				{ xpos,     ypos,       0.0f, 0.0f },
				{ xpos,     ypos + h,   0.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 1.0f },

				{ xpos,     ypos,       0.0f, 0.0f },
				{ xpos + w, ypos + h,   1.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textId);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		x += float(ch.advance.x >> 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}



oui_err Font::Initialize(util::Shader *shader) {
	if(glyphShader) {
		return OUI_ENONE;
	}

	glyphShader = shader;

	// gl enables
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (FT_Init_FreeType(&ft)) {
		log_critf("failed to initialize freetype library");
		glyphShader = 0;
		return OUI_ECRITICAL;
	}

	return OUI_ENONE;
}

oui_err Font::Orthographic(unsigned int width
		, unsigned int height
		, unsigned int depth) {
	if(!glyphShader) {
		return OUI_EINVAL;
	}
	glm::mat4 projection = glm::ortho(0.0f
			, float(width)
			, float(height)
			, 0.0f
			, float(depth)
			, 0.0f);
	glyphShader->use();
	glUniformMatrix4fv(
			glGetUniformLocation(glyphShader->ID, "projection")
			, 1
			, GL_FALSE
			, glm::value_ptr(projection));
	return OUI_ENONE;
}

void Font::Free() {
	FT_Done_FreeType(ft);
}



