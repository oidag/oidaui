#include <oidaui/oidaui.h>
#include "canvas.hpp"

int odui_alloc(odui_canvas **o_canvas) {
	Canvas *ret = new Canvas();
	*o_canvas = (odui_canvas *)ret;
	return 0;
}


int odui_free(odui_canvas *canvas) {
	Canvas *c = (Canvas *)canvas;
	delete c;
	return 0;
}

int odui_draw(odui_canvas *canvas) {
	Canvas *c = (Canvas *)canvas;
	c->draw();
	return 0;
}

int odui_add(odui_element *parent, odui_element *child) {
	Element *p = (Element *)parent;
	Element *c = (Element *)child;
	return p->addElement(c);
}