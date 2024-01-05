#ifndef OIDAUI_FONT_HPP
#define OIDAUI_FONT_HPP

#include <oidaui/oidaui.h>

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
	 *
	 */
	void render();

private:
	struct oui_typeface_config config;
	unsigned int characterc;
	struct character *characterv;
};

oui_err Initialize();
void Free();

}

#endif //OIDAUI_FONT_HPP
