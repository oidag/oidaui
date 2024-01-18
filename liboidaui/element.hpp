#ifndef OIDAUI_ELEMENT_HPP
#define OIDAUI_ELEMENT_HPP

#include "canvas.hpp"

namespace canvas {

class Element : public Node {
public:
	/**
	 * If element is not supplied with canvas, then the one from the cursor
	 * is used.
	 */
	Element();

	explicit Element(Canvas *canvas);

	~Element();

protected:


private:

	void draw(oui_layout_t layout);
	void preDraw() const;
	void postDraw() const;
	void init(Canvas *canvas);

	friend class Canvas;
};

}

#endif //OIDAUI_ELEMENT_HPP
