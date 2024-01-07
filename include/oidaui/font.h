#ifndef OIDAUI_FONT_H
#define OIDAUI_FONT_H

#include "error.h"
#include "common.h"

struct oui_font_measurement {

	// the overall pixel width of the text
	int width;

	// baselineAbove + baselineBelow
	int height;

	// pixels above the baseline
	int baselineAbove;

	// pixels below the baseline
	int baselineBelow;
};

struct oui_typeface_config {

	// at least one of these must be set. If the other is set to 0, then it
	// is dynamically calculated. Normally, you'd only want to specify the
	// height.
	unsigned int pixelHeight;
	unsigned int pixelWidth;

	//
	unsigned int charCodeStart;
	unsigned int charCodeLen;
};

typedef void oui_typeface;

export oui_err oui_typeface_alloc(const char *path
		, struct oui_typeface_config
		, oui_typeface **o_typeface);
export oui_err oui_typeface_free(oui_typeface *typeface);


#endif //OIDAUI_FONT_H
