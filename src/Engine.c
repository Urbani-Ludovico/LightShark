
#include "Engine.h"

struct ls_t {

};

ls_t ls_init() {
    const auto engine = (ls_t)calloc(1, sizeof(struct ls_t));

    return engine;
}

void ls_destroy(const ls_t engine) {
    free(engine);
}