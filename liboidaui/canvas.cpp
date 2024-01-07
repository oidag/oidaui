//
// Created by kmarschke on 1/2/24.
//

#include <oidaui/oidaui.h>
#include "canvas.hpp"


Canvas::Canvas()  : Element(){

}

Canvas::~Canvas()  {

}

void Canvas::draw() {
	glClearColor(1,0,0,1);
}

int Canvas::addElement(Element *elm) {
	return 0;
}


