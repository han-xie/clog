#include <stdio.h>

#include "clog.h"

int main() {
    int r;

    /* Initialize the logger */
    r = clog_init_path("my_log.txt");
    if (r != 0) {
        fprintf(stderr, "Logger initialization failed.\n");
        return 1;
    }

    /* Set minimum log level to info (default: debug) */
    clog_set_level(CLOG_INFO);

    /* Write a message */
    clog_info(CLOG, "Hello, %s!", "world");

    /* Clean up */
    clog_free();
    return 0;
}
