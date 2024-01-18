#ifndef OIDAUI_CANVAS_HPP
#define OIDAUI_CANVAS_HPP

#include <oidaui/oidaui.h>
#include "node.hpp"

namespace canvas {

class Canvas;



class Canvas final : Node {
public:
	Canvas();
	~Canvas();

	void draw(oui_layout_t layout) final;

	/**
	 * If an element is managed by the canvas, that means that when the canvas
	 * is destructed, it will implicitly destruct all managed elements as well.
	 *
	 * Not sure why you would ever need to relinquish a managed element, but
	 * there you go. relinquish is safe to call in the element's destructor (
	 * despite the chance that destructor is being executed because the canvas's
	 * destructor was called first and thus is invoking its managed elements'
	 * destructors).
	 */
	void manage(Node *e);
	void relinquish(Node *e);

private:
	// just to satsify Node
	oui_bounds_t getBounds() override {return oui_bounds_t{};};

	int       managedq = 0;
	Node    **managedv = 0;
	int       managedc = 0;

	bool      destructing = false;
};

oui_err Initialize();
void Free();

}


#endif //OIDAUI_CANVAS_HPP
