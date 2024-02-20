#include "main.h"

int main(const int argc, const char *argv[]) {
    if (argc == 1) {
        no_args();
    } else {
        parse_args(argc, argv);
    }
    return 0;
}
