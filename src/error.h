#include "types.h"

#ifndef _ERROR_
#define _ERROR_

/***
 * configure error handling
 */
void error_init();

/***
 * display error with given number
 */
void err_display(uint8_t err);

#endif
