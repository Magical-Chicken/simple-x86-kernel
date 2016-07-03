#include "types.h"

#ifndef _CONSOLE_
#define _CONSOLE_

/***
 * publicly accessible interfaces
 */
enum console_interfaces {
    CONSOLE_INTERFACE_NULL,
    CONSOLE_INTERFACE_VGA,
};

/***
 * interface config
 */
struct console_interface {
    bool enabled;
    void (*init)();
    void (*clear)();
    void (*newline)();
    void (*putchar)(char);
};

/***
 * prep console, init and connect interfaces
 */
void console_init();
void console_connect_interface(enum console_interfaces interface);

/***
 * output text and handle special characters
 */
void console_puts(const char *str);

#endif
