
#include "LSEngine.h"

ls_t ls_init() {
    auto const engine = (ls_t)malloc(sizeof(struct _ls_t));

    // Start tree
    engine->tree = ls_tree_init();
    engine->state = engine->tree;

    // Start first board
    engine->tree->board = ls_board_init();
    engine->board = engine->tree->board;
    engine->state->turn = LS_PLAYER_WHITE;
    ls_board_start(engine->board);

    // Game status
    engine->turn = LS_PLAYER_WHITE;
    engine->moves_count = 0;
    engine->captured_white_queen = 0;
    engine->captured_white_rock = 0;
    engine->captured_white_knight = 0;
    engine->captured_white_bishop = 0;
    engine->captured_white_pawn = 0;
    engine->captured_black_queen = 0;
    engine->captured_black_rock = 0;
    engine->captured_black_knight = 0;
    engine->captured_black_bishop = 0;
    engine->captured_black_pawn = 0;

    return engine;
}

void ls_destroy(const ls_t engine) {
    ls_tree_destroy(engine->tree);

    free(engine);
}
