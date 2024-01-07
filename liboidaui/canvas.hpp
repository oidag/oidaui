#ifndef OIDAUI_CANVAS_HPP
#define OIDAUI_CANVAS_HPP


#include <GL/gl.h>
#include <oidaui/oidaui.h>

#include "element.hpp"

class Canvas: public Element {
public:
	Canvas();
	~Canvas();
	void draw();
	int addElement(Element *elm);
};

class PixelPos {
public:
	explicit PixelPos(struct oui_pixel p) {pixel = p;};
	explicit operator struct oui_pixel() {return pixel;};

private:
	struct oui_pixel pixel{};
};


#endif //OIDAUI_CANVAS_HPP
