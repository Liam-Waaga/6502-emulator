
#include "log.h"

#include <cstdlib>
#include <exception>

int main() {
    try {
        logf(INFO, "This is a test %d %s", 42, "yuppy");
    } catch (std::exception& e) {
        logf(ERROR, "Uncaught exception \"%s\"", e.what());
        std::exit(1);
    }
}