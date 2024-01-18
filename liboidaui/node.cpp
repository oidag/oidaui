#include "node.hpp"
#include "errors.h"
#include "canvas.hpp"
#include <malloc.h>


void canvas::Node::addChild(canvas::Node *child) {
	if(this->canvas != child->canvas) {
		log_errorf(_("cannot add a child to a node not belonging to the same canvas"));
		return;
	}
	if(!child->parent) {
		child->parent->removeChild(child);
	}
	if (this->childrenc == this->childrenq) {
		this->childrenq += 8;
		this->childrenv = (Node **)realloc(this->childrenv, this->childrenq * sizeof(Node *));
	}
	child->childIndex = this->childrenc;
	this->childrenv[this->childrenc] = child;
	this->childrenc++;
	child->parent = this;
}

canvas::Node **canvas::Node::getChildren(int *o_childrenc) const {
	*o_childrenc = this->childrenc;
	return this->childrenv;
}

void canvas::Node::removeChild(canvas::Node *child) {
	if(child->parent != this) {
		return;
	}

	// shift all the elements over
	for(int i = child->childIndex; i < this->childrenc - 1; i++) {
		this->childrenv[i] = this->childrenv[i+1];
	}

	child->parent = nullptr;
	child->childIndex = 0;

	this->childrenc--;
}

canvas::Node::~Node() {
	if(this->parent) {
		this->parent->removeChild(this);
	}
	if(this->childrenv) {
		free(this->childrenv);
	}
}

bool canvas::Node::attached() const {
	return this->parent && this->canvas;
}

canvas::Canvas *canvas::Node::getCanvas() const {
	return this->canvas;
}
