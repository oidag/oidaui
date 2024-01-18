#ifndef OIDAUI_CANVAS_HPP
#define OIDAUI_CANVAS_HPP

#include <GL/gl.h>
#include <oidaui/oidaui.h>

namespace canvas {

class Element;
class Canvas;

class IParent {
public:
	~IParent();

	virtual void addChild(Element *) final;
	virtual void removeChild(canvas::Element *child) final;
	virtual Element **getChildren(int *o_childrenc) const final;

private:
	int       childrenq = 0;
	Element **childrenv = 0;
	int       childrenc = 0;
	int       childID = 0;
};

class Element : public IParent {
public:
	/**
	 * If element is not supplied with canvas, then the one from the cursor
	 * is used.
	 */
	Element();
	explicit Element(Canvas *canvas);

	virtual ~Element();

	virtual struct oui_bounds getBounds() = 0;
	virtual struct oui_vec3 getPosition() = 0;
	virtual void setSize(struct oui_vec3) = 0;

	/**
	 * Returns the canvas that is managing the element.
	 */
	Canvas *getCanvas() const;

protected:
	virtual void draw() = 0;

private:
	void preDraw() const;
	void postDraw() const;
	IParent *parent = 0;
	Canvas *canvas = 0;
	int canvasID = 0;

	void init(Canvas *canvas);

	friend class IParent;
	friend class Canvas;
};


class Canvas final {
public:
	Canvas();
	~Canvas();
	void draw();

	/**
	 * If an element is managed by the canvas, that means that when the canvas
	 * is destructed, it will implicitly destruct all managed elements as well.
	 *
	 *
	 * Not sure why you would ever need to relinquish a managed element, but
	 * there you go.
	 */
	void manage(Element *e);
	void relinquish(Element *e);

private:
	int       managedq = 0;
	Element **managedv = 0;
	int       managedc = 0;
};

oui_err Initialize();
void Free();

}


#endif //OIDAUI_CANVAS_HPP
