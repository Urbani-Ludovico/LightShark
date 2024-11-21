
#include "create.h"

int example_create() {
    const ls_t engine = ls_init();

    ls_board_print(engine->board);

    return 0;
}