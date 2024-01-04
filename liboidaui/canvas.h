#ifndef OIDAUI_CANVAS_H
#define OIDAUI_CANVAS_H


#include <GL/gl.h>

#include "element.h"

class Canvas: public Element {
public:
	Canvas();
	~Canvas();
	void draw();
	int addElement(Element *elm);
};


#endif //OIDAUI_CANVAS_H
