#include "canvas.hpp"
#include "element.hpp"
#include "cursor.hpp"

canvas::Element::Element() {
	this->init(cursor.canvas);
}

canvas::Element::Element(canvas::Canvas *canvas) {
	this->init(canvas);
}

void canvas::Element::init(canvas::Canvas *c) {
	Node *parent = cursor.parent;
	c->manage(this);
	parent->addChild(this);
}

canvas::Element::~Element() {
	Canvas *c = this->getCanvas();
	if(c) {
		c->relinquish(this);
	}
}




