#ifndef OIDAUI_OIDAUI_H
#define OIDAUI_OIDAUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "common.h"
#include "font.h"

typedef void odui_element;

typedef void odui_canvas;

export oui_err oui_init();
export void oui_free();

export int odui_alloc(odui_canvas **o_canvas);
export int odui_free(odui_canvas *canvas);
export int odui_draw(odui_canvas *canvas);
export int odui_add(odui_element *parent, odui_element **childrenv, int childrenc);

// oui_pixel - (0,0) will be the top left of the canvas.
typedef struct oui_pixel {
	int x;
	int y;
} oui_pixel_t;

typedef struct oui_vec3 {
	union {
		int x;
		int width;
	};
	union {
		int y;
		int height;
	};
	union {
		int z;
		int depth;
	};
} oui_vec3_t;

typedef struct oui_layout {
	oui_vec3_t dimensions;
	oui_vec3_t location;
} oui_layout_t;

typedef struct oui_bounds {
	struct oui_vec3 max;
	struct oui_vec3 min;
} oui_bounds_t;


#ifdef __cplusplus
}
#endif

#endif //OIDAUI_OIDAUI_H
