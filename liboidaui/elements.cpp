#include "canvas.hpp"
#include "cursor.hpp"

void canvas::Element::preDraw() const {

}

void canvas::Element::postDraw() const {

}

canvas::Canvas *canvas::Element::getCanvas() const {
	return this->canvas;
}

canvas::Element::Element() {
	this->init(cursor.canvas);
}

canvas::Element::Element(canvas::Canvas *canvas) {
	this->init(canvas);
}

void canvas::Element::init(canvas::Canvas *c) {
	this->parent = cursor.parent;
	c->manage(this);
	this->parent->addChild(this);
}

canvas::Element::~Element() {
	if(this->parent) {
		this->parent->removeChild(this);
	}
}


void canvas::IParent::addChild(canvas::Element *child) {
	if(!child->parent) {
		child->parent->removeChild(child);
	}
	if (this->childrenc == this->childrenq) {
		this->childrenq += 8;
		this->childrenv = (Element **)realloc(this->childrenv, this->childrenq * sizeof(Element *));
	}
	child->childID = this->childrenc;
	this->childrenv[this->childrenc] = child;
	this->childrenc++;
	child->parent = this;
}

canvas::Element **canvas::IParent::getChildren(int *o_childrenc) const {
	*o_childrenc = this->childrenc;
	return this->childrenv;
}

void canvas::IParent::removeChild(canvas::Element *child) {
	if(child->parent != this) {
		return;
	}

	// shift all the elements over
	for(int i = child->childID; i < this->childrenc-1; i++) {
		this->childrenv[i] = this->childrenv[i+1];
	}

	child->parent = 0;
	child->childID = 0;

	this->childrenc--;
}

canvas::IParent::~IParent() {
	if(this->childrenv) {
		free(this->childrenv);
	}
}
