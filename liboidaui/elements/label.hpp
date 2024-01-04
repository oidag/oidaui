#ifndef OIDAUI_LABEL_HPP
#define OIDAUI_LABEL_HPP

#include "../element.hpp"

class Label : public Element {
public:
	Label(const char *text);
	~Label();


	void draw();

	// note: may not always do something. returns non-0 if the action failed.
	//virtual int addElement(Element *elm) {return 1;};
};


#endif //OIDAUI_LABEL_HPP
