//
// Created by kmarschke on 1/2/24.
//

#ifndef OIDAUI_ELEMENT_H
#define OIDAUI_ELEMENT_H

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
	Element(){this->bounds={0};};
	virtual ~Element(){};

	// When draw is called,
	virtual void draw();

	Bounds getBounds() {return this->bounds;}
	Position getPosition() {return this->position;}

protected:
	Bounds bounds;
	Position position;

};

class ElementContainer: Element {
public:
	virtual void addElement(Element *elm);

};


#endif //OIDAUI_ELEMENT_H
