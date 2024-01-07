#include <oidaui/oidaui.h>
#include "canvas.hpp"
#include "font/font.hpp"

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


oui_err oui_init() {
	oui_err err;
	if ((err = Font::Initialize(0, 0))) {
		return err;
	}
}

void oui_free() {
	Font::Free();
}