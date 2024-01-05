#ifndef OIDAUI_ERROR_H
#define OIDAUI_ERROR_H

typedef enum {
	OUI_ENONE,
	OUI_ECRITICAL,
} oui_err;

const char *oui_errstr(oui_err error);

#endif //OIDAUI_ERROR_H