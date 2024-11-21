#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>

struct _ls_t;
typedef struct _ls_t* ls_t;

ls_t ls_init();
void ls_destroy(ls_t engine);

#endif
