

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include <oidaui/oidaui.h>
#include "canvas.hpp"
#include "element.hpp"
#include "node.hpp"
#include "font/font.hpp"
#include "util/shader.hpp"
#include "errors.h"


canvas::Canvas::Canvas() {

}

canvas::Canvas::~Canvas() {

	// this will prevent us from destructing elements just to have then
	// invoke relinquish and screwing with our managed array.
	destructing = true;

	if(managedv) {
		for(int i = 0; i < managedc; i++) {
			delete managedv[i];
		}
		free(managedv);
	}
}

void canvas::Canvas::draw(oui_layout_t layout) {

	// draw self
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0.2,0,1);

	// children
	for(int i = 0; i < this->childrenc; i++) {
		Node *e = this->childrenv[i];
		Node *parent = e->parent;
		e->draw(layout);
	}
}

void canvas::Canvas::manage(canvas::Node *child) {
	if(child->canvas == this) return;
	if(child->canvas) {
		log_warnf("cannot managed element as its already managed");
		return;
	}
	if (this->managedc == this->managedq) {
		this->managedq += 8;
		this->managedv = (Node **)realloc(this->managedv, this->managedq * sizeof(Node *));
	}
	child->canvasIndex = this->managedc;
	this->managedv[this->managedc] = child;
	this->managedc++;
	child->canvas = this;
}

void canvas::Canvas::relinquish(canvas::Node *e) {
	if(this->destructing) return;
	if(!e->canvas) {
		return;
	}
	if(e->canvas != this) {
		log_warnf("cannot relinquish element as it does not belong to canvas");
		return;
	}
	this->managedv[e->canvasIndex] = nullptr;
	e->canvas = nullptr;
	// shift over
	for(int i = e->canvasIndex; i < this->managedc - 1; i++) {
		this->managedv[i] = this->managedv[i+1];
	}
}

util::Shader *fontShader;
oui_err canvas::Initialize() {
	fontShader = new util::Shader("shaders/glyph.vert", "shaders/glyph.frag");
	Font::Initialize(fontShader);
	return OUI_ENONE;
}

void canvas::Free() {
	delete fontShader;
	Font::Free();
}

