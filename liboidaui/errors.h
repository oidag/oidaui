#ifndef OUI_ERRORS_H
#define OUI_ERRORS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <oidaui/error.h>
#include "locale.h"

#define log_critf(fmt, ...) _log_critf(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

// with crits, if you have an errno to complain about make sure you don't purge it
// as log_crit will look at errno and log what ever it is at the time.
//
// log_critf will preserve errno.
//
// log_critf will always return ODB_ECRIT
oui_err _log_critf(const char *file, int line, const char *fmt,
                   ...) __attribute__ ((format (printf, 3, 4)));

void log_error(const char *log);

void log_errorf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void log_noticef(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void log_alertf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void log_info(const char *log);

void log_infof(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void log_warn(const char *log);

void log_warnf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void log_debug(const char *log);

void log_debugf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* OUI_ERRORS_H */