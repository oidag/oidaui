#ifndef OIDAUI_FONT_HPP
#define OIDAUI_FONT_HPP

#include <glm/glm.hpp>
#include <oidaui/oidaui.h>

#include "../util/shader.hpp"

namespace Font {

struct character;
const struct oui_typeface_config fontConfigDefault{
		.pixelHeight = 16,
		.pixelWidth = 0,
		.charCodeStart = 0,
		.charCodeLen = 128,
};


class TypeFace {
public:
	TypeFace();
	~TypeFace();

	oui_err load(const char *path, struct oui_typeface_config);

	/**
	 * Render the text on the screen with its baseline starting at pixel (X,Y).
	 * See TypeFace::size for accurate placement.
	 */
	void render(const wchar_t *text, float x, float y, glm::vec3 color);

	/**
	 * Calculate the width and height of the bounding box around a given text.
	 */
	oui_font_measurement size(const wchar_t *text);

private:
	struct oui_typeface_config config{};
	unsigned int characterc{};
	struct character *characterv{};
	unsigned int VAO{}, VBO{};
};

void Test(unsigned int width, unsigned int height);

/**
 * After Initialized returns successfully, make sure to call Orthographic
 * to update the Font rendering matrix initially, and call Orthographic
 * every subsequent matrix update.
 */
oui_err Initialize(util::Shader *shader);
oui_err Orthographic(unsigned int width
					 , unsigned int height
					 , unsigned int depth);
void Free();

}

#endif //OIDAUI_FONT_HPP
