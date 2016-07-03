#include "console.h"
#include "types.h"
#include "serial.h"
#include "vga.h"

/***
 * number of registered interfaces
 */
#define INTERFACE_COUNT 2

/***
 * make call on all active interfaces
 *
 * note: clobbers i
 */
#define CALL_ON_ACTIVE(i, call) \
    do {                                            \
        for (i = 0; i < INTERFACE_COUNT; i++)       \
            if ((*INTERFACE_REGISTRY[i]).enabled)   \
                (*INTERFACE_REGISTRY[i]).call;      \
    } while(0)

/***
 * null interface functions
 */
void null_conf() { }
void null_putchar(char c) { }

/***
 * interface specifications
 */
static struct console_interface CONSOLE_INTERFACE_VGA_SETUP = {
    .enabled    = false,
    .init       = &vga_init,
    .clear      = &vga_clear,
    .newline    = &vga_newline,
    .putchar    = &vga_putchar,
};

static struct console_interface CONSOLE_INTERFACE_NULL_SETUP = {
    .enabled    = false,
    .init       = &null_conf,
    .clear      = &null_conf,
    .newline    = &null_conf,
    .putchar    = &null_putchar,
};

/***
 * all registered interfaces
 */
static struct console_interface *INTERFACE_REGISTRY[INTERFACE_COUNT];

/***
 * prep console
 */
void console_init() {
    // register interfaces
    INTERFACE_REGISTRY[CONSOLE_INTERFACE_NULL] = &CONSOLE_INTERFACE_NULL_SETUP;
    INTERFACE_REGISTRY[CONSOLE_INTERFACE_VGA]  = &CONSOLE_INTERFACE_VGA_SETUP;
}

/***
 * connect interface
 */
void console_connect_interface(enum console_interfaces interface) {
    (*INTERFACE_REGISTRY[interface]).enabled = true;
    (*INTERFACE_REGISTRY[interface]).init();
}

/***
 * output text and handle special characters
 */
void console_puts(const char *str) {
    int i;
    char cur;
    while ((cur = *str++) != NULL) {
        switch (cur) {
            case '\r': // fall through to newline
            case '\n': CALL_ON_ACTIVE(i, newline());    break;
            case '\t': CALL_ON_ACTIVE(i, putchar(' ')); break;
            default:   CALL_ON_ACTIVE(i, putchar(cur)); break;
        }
    }
}

/***
 * clear console
 */
void console_clear() { int i; CALL_ON_ACTIVE(i, clear()); }
