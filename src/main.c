#include "headers/main.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s <run name>\n", argv[0]);
        return 1;
    }

    // srand(time(NULL));
    srand(0);

    run_md(argv[1], true);

    return 0;
}