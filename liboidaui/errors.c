#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

#include <oidaui/oidaui.h>
#include "errors.h"

#define stdlogthing(stream,prefix) { \
	int terr = errno; \
va_list args; \
va_start(args, fmt); \
fprintf(stream, prefix ": ");\
vfprintf(stream, fmt, args); \
fprintf(stream, "\n"); \
if(terr) { \
errno = terr; \
perror(prefix " (had errno)"); \
} \
va_end(args);\
errno = terr;}


oui_err _log_critf(const char *file, int line, const char *fmt, ...) {
	int terr = errno;
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "crit: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	if(terr) {
		errno = terr;
		perror("crit" " (had errno)");
	}
	va_end(args);
	errno = terr;
	return OUI_ECRITICAL;
}

void log_error(const char *log) {
	log_errorf("%s", log);
}
void log_errorf(const char *fmt, ...) {
	stdlogthing(stderr, "error");
}

void log_debug(const char *log) {
	log_debugf("%s", log);
}
void log_debugf(const char *fmt, ...)  {
	stdlogthing(stdout, "debug");
}

void log_noticef(const char *fmt, ...) {
	stdlogthing(stdout, "notice");
}

void log_alertf(const char *fmt, ...) {
	stdlogthing(stdout, "notice");
}


void log_info(const char *log) {
	log_infof("%s", log);
}
void log_infof(const char *fmt, ...) {
	stdlogthing(stdout, "info");
}

void log_warnf(const char *fmt, ...) {
	stdlogthing(stdout, "warn");
}

void implementme() {

	// cause a segfaut and div0.
	int *throw = (void *)(0);
	*throw = 1;
}

const char *oui_errstr(oui_err error) {
	switch (error) {
		case OUI_ENONE:     return "OUI_ENONE";
		case OUI_ECRITICAL: return "OUI_ECRIT";
		default: return "UNDOCUMENTEDERROR";
	}
}