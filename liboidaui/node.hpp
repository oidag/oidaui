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

	/**
	 * Add child nodes to this element. If the child node already has
	 * a parent, then the child is removed from that parent implicitly.
	 *
	 * The child will become managed by the parent's canvas (if the parent is
	 * already being managed)
	 *
	 * Errors:
	 *  - OUI_ERECURSE - caller is trying to add a parent node to
	 *    a child node (child->hasDescendant didn't return -1)
	 */
	virtual oui_err addChild(Node *child) final;

	/**
	 * Remove the child node from this parent. This will also relinquish the
	 * node from the canvas (if that has been set)
	 *
	 * Errors:
	 *  - OUI_ENORECURSE (removeChild) - child doesn't belong to this parent
	 */
	virtual oui_err removeChild(canvas::Node *child) final;

	/**
	 * If node is not a descendant of this, then -1 is returned. Otherwise, the
	 * level of descendant is returned. With 0 being the fact that this node
	 * is the same as this, 1 being a child, 2 being a great child, ect.
	 */
	virtual int hasDescendant(Node *node) final;

	/**
	 * Returns all direct children of this node, with *o_children being set to
	 * the size of the returned array.
	 */
	virtual Node **getChildren(int *o_childrenc) const final;

	/**
	 * Returns the canvas that is managing this element, or otherwise null
	 * if this element is not managed by a canvas.
	 */
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

	Canvas   *canvas = 0;
	Node     *parent = 0;
	int       childrenq = 0;
	Node    **childrenv = 0;
	int       childrenc = 0;
	int       childIndex = 0;
	int       canvasIndex = 0;

	friend class Canvas;
};

} // canvas

#endif //OIDAUI_NODE_HPP
