#include <sstream>
#include <unistd.h>

#include "clog.h"

#include "clog_test.h"
#include "clog_test_cpp.h"

#undef  __STRICT_ANSI__
#define THIS_FILE "clog_test_cpp.cpp"

int test_cpp_hello()
{
    std::ostringstream message;
    char buf[1024];
    int fd[2];

    message << "Hello, " << "world!";

    CHECK_CALL(pipe(fd));
    CHECK_CALL(clog_init_fd(fd[1]));
    CHECK_CALL(clog_set_fmt("%f: %l: %m\n"));
    clog_debug(CLOG, "%s", message.str().c_str());
    clog_free();
    close(fd[1]);

    size_t bytes = read(fd[0], buf, 1024);
    if (bytes <= 0) {
        close(fd[0]);
        return 1;
    }
    buf[bytes] = 0;
    close(fd[0]);
    CHECK_CALL(strcmp(buf, THIS_FILE ": DEBUG: Hello, world!\n"));

    return 0;
}
