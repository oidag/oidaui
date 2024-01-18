//
// Created by kmarschke on 1/2/24.
//

#include <oidaui/oidaui.h>
#include "canvas.hpp"
#include "font/font.hpp"
#include "cursor.hpp"
#include "util/shader.hpp"
#include "errors.h"


canvas::Canvas::Canvas() {
}

canvas::Canvas::~Canvas() {
	if(managedv) {
		for(int i = 0; i < managedc; i++) {
			delete managedv[i];
		}
		free(managedv);
	}
}

void canvas::Canvas::draw() {

	glClearColor(0.0f, 0.3f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < this->managedc; i++) {
		managedv[i]->preDraw();
		managedv[i]->draw();
		managedv[i]->postDraw();
	}
}

void canvas::Canvas::manage(canvas::Element *child) {
	if(child->canvas == this) return;
	if(child->canvas) {
		log_warnf("cannot managed element as its already managed");
		return;
	}
	if (this->managedc == this->managedq) {
		this->managedq += 8;
		this->managedv = (Element **)realloc(this->managedv, this->managedq * sizeof(Element *));
	}
	child->canvasID = this->managedc;
	this->managedv[this->managedc] = child;
	this->managedc++;
	child->canvas = this;
}

void canvas::Canvas::relinquish(canvas::Element *e) {
	if(!e->canvas) {
		return;
	}
	if(e->canvas != this) {
		log_warnf("cannot relinquish element as it does not belong to canvas");
		return;
	}
	this->managedv[e->canvasID] = 0;
	e->canvas = 0;
	// shift over
	for(int i = e->canvasID; i < this->managedc-1; i++) {
		this->managedv[i] = this->managedv[i+1];
	}
}

util::Shader *fontShader;
oui_err canvas::Initialize() {
	fontShader = new util::Shader("shaders/glyph.vert", "shaders/glyph.frag");
	Font::Initialize(fontShader);
}

void canvas::Free() {
	delete fontShader;
	Font::Free();
}

