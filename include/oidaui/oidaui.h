#ifndef OIDAUI_OIDAUI_H
#define OIDAUI_OIDAUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"

#define export __attribute__((__visibility__("default")))


typedef void odui_element;

typedef void odui_canvas;

export int odui_alloc(odui_canvas **o_canvas);
export int odui_free(odui_canvas *canvas);
export int odui_draw(odui_canvas *canvas);
export int odui_add(odui_element *parent, odui_element **childrenv, int childrenc);


#ifdef __cplusplus
}
#endif

#endif //OIDAUI_OIDAUI_H
