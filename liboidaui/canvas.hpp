#ifndef OIDAUI_CANVAS_HPP
#define OIDAUI_CANVAS_HPP


#include <GL/gl.h>

#include "element.hpp"

class Canvas: public Element {
public:
	Canvas();
	~Canvas();
	void draw();
	int addElement(Element *elm);
};


#endif //OIDAUI_CANVAS_HPP
