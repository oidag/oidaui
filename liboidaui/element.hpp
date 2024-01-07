#ifndef OIDAUI_ELEMENT_HPP
#define OIDAUI_ELEMENT_HPP

#include "./font/font.hpp"

class Bounds {
public:
	unsigned int widthMax;
	unsigned int widthMin;
	unsigned int heightMax;
	unsigned int heightMin;
};
class Position {
public:
	unsigned int x;
	unsigned int y;
	unsigned int z;
};

class Element {
public:
	Element();
	virtual void draw() = 0;

	// note: may not always do something. returns non-0 if the action failed.
	virtual int addElement(Element *elm) {return 1;};

	Bounds getBounds() {return this->bounds;}
	Position getPosition() {return this->position;}

	virtual void setFont(TypeFace *f);

protected:
	Bounds bounds{0};
	Position position{0};

};

#endif //OIDAUI_ELEMENT_HPP
