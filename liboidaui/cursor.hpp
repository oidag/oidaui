#ifndef OIDAUI_CURSOR_HPP
#define OIDAUI_CURSOR_HPP

#include "canvas.hpp"
#include "font/font.hpp"

/**
 * The "cursor" is the system that manages what is used when creating new
 * elements. Think of it as setting the default arguments of newly created
 * items.
 */

namespace canvas {

struct {


	/**
	 * Some elements can have a font be set. This property will not effect
	 * all elements
	 */
	Font::TypeFace *font;

	/**
	 * what new elements will automatically be added to when created.
	 */
	IParent *parent;

} cursor;


}

#endif //OIDAUI_CURSOR_HPP
