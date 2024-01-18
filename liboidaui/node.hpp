#ifndef OIDAUI_NODE_HPP
#define OIDAUI_NODE_HPP

#include <oidaui/oidaui.h>

namespace canvas {

class Canvas;

/**
 * A node is defined as anything that has a parent and children. The highest
 * level parent is the canvas itself. A node also contains a pointer to said
 * canvas. A node can only belong to a canvas if its both a decendent of that
 * canvas as well as managed by that canvas.
 *
 * If a node has a parent and a canvas, then its considered fully attached and
 * will be drawn.
 *
 * If a node does not have a parent, or, doesn't have a canvas,
 * it's considered "unattached" meaning it will not be drawn.
 *
 * If a node does not have a parent but has a canvas, it's still considered
 * its considered managed not still attached.
 *
 * Technically a Canvas is also a node, but it will not have a parent node.
 */
class Node {
public:
	~Node();

	/**
	 * returns true if the node has a parent and canvas, thus visible on the
	 * canvas and should be drawn.
	 */
	virtual bool attached() const final;
	virtual void addChild(Node *) final;
	virtual void removeChild(canvas::Node *child) final;

	virtual Node **getChildren(int *o_childrenc) const final;
	virtual Canvas *getCanvas() const final;


	virtual oui_bounds_t getBounds() = 0;

protected:

	/**
	 * Draw yourself with the given layout, then draw the children you have
	 * (if applicable).
	 *
	 * When drawing children, you must invoke their draw() method with a layout
	 * that you calculate. You children's layout must be contained within your
	 * own layout
	 */
	virtual void draw(oui_layout_t layout) = 0;

private:

	Node     *parent = 0;
	Canvas   *canvas = 0;
	int       childrenq = 0;
	Node    **childrenv = 0;
	int       childrenc = 0;
	int       childIndex = 0;
	int       canvasIndex = 0;

	friend class Canvas;
};

} // canvas

#endif //OIDAUI_NODE_HPP
