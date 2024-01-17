#ifndef OIDAUI_CANVAS_HPP
#define OIDAUI_CANVAS_HPP

#include <GL/gl.h>
#include <oidaui/oidaui.h>

namespace canvas {

class IDrawable {
public:
	virtual void draw() = 0;
	virtual struct oui_bounds getBounds() = 0;

	virtual struct oui_vec3 getPosition() = 0;
	virtual void setSize(struct oui_vec3) = 0;
};

class IParent {
public:
	virtual void addChild(IDrawable) = 0;
};

class Canvas : public IParent {
public:
	Canvas();

	~Canvas();

	void addChild(IDrawable);

	void draw();
};

}


#endif //OIDAUI_CANVAS_HPP
