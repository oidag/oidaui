#include "node.hpp"
#include "errors.h"
#include "canvas.hpp"
#include <malloc.h>


oui_err canvas::Node::addChild(canvas::Node *child) {
	if(child->hasDescendant(this) != -1) {

		// caller is trying to add a parent node to a child node, which
		// would cause an inclusion loop.

		return OUI_ERECURSE;
	}

	if(child->parent) {
		child->parent->removeChild(child);
	}

	if(!child->canvas && this->canvas) {
		this->canvas->manage(child);
	}

	if (this->childrenc == this->childrenq) {
		this->childrenq += 8;
		this->childrenv = (Node **)realloc(this->childrenv, this->childrenq * sizeof(Node *));
	}
	child->childIndex = this->childrenc;
	this->childrenv[this->childrenc] = child;
	this->childrenc++;
	child->parent = this;
	return OUI_ENONE;
}

oui_err canvas::Node::removeChild(canvas::Node *child) {

	if(child->parent != this) {
		return OUI_ENORECURSE;
	}

	// shift all the elements over
	for(int i = child->childIndex; i < this->childrenc - 1; i++) {
		this->childrenv[i] = this->childrenv[i+1];
	}

	child->parent = nullptr;
	child->childIndex = 0;
	this->childrenc--;

	if(child->canvas) {
		child->canvas->relinquish(child);
	}
	return OUI_ENONE;
}

canvas::Node **canvas::Node::getChildren(int *o_childrenc) const {
	*o_childrenc = this->childrenc;
	return this->childrenv;
}

canvas::Node::~Node() {
	if(this->parent) {
		this->parent->removeChild(this);
	}
	if(this->childrenv) {
		free(this->childrenv);
	}
	Canvas *c = this->getCanvas();
	if(c) {
		c->relinquish(this);
	}
}

bool canvas::Node::attached() const {
	return this->parent && this->canvas;
}

canvas::Canvas *canvas::Node::getCanvas() const {
	return this->canvas;
}

int canvas::Node::hasDescendant(canvas::Node *node) {
	int i = 0;
	while(true) {
		if (node == this) {
			break;
		}
		if(!node->parent) {
			return -1;
		}
		node = node->parent;
		i++;
	}

	return i;
}
