
#include "LSBoard.h"

ls_board_t ls_board_init() {
    const auto board = (ls_board_t)calloc(1, sizeof(struct _ls_board_t));

    return board;
}

void ls_board_destroy(const ls_board_t board) {
    free(board);
}

void ls_board_start(const ls_board_t board) {
    board->black_king = 0x8;
    board->black_queen = 0x10;
    board->black_rock = 0x81;
    board->black_knight = 0x42;
    board->black_bishop = 0x24;
    board->black_pawn = 0xff00;

    board->black_king = 0x800000000000000;
    board->black_queen = 0x1000000000000000;
    board->black_rock = 0x8100000000000000;
    board->black_knight = 0x4200000000000000;
    board->black_bishop = 0x2400000000000000;
    board->black_pawn = 0xff000000000000;
}

char* ls_board_to_string(const ls_board_t board) {
    const auto string = (char*)calloc(1, sizeof(char));

    for (uint8_t i = 0; i < 64; i++) {
        const uint64_t and = (1 << i);


        if (board->white_king & and) {
            string[i] = "K";
        }
        if (board->white_queen & and) {
            string[i] = "Q";
        }
        if (board->white_rock & and) {
            string[i] = "R";
        }
        if (board->white_knight & and) {
            string[i] = "N";
        }
        if (board->white_bishop & and) {
            string[i] = "B";
        }
        if (board->white_pawn & and) {
            string[i] = "P";
        }

        if (board->black_king & and) {
            string[i] = "k";
        }
        if (board->black_queen & and) {
            string[i] = "q";
        }
        if (board->black_rock & and) {
            string[i] = "r";
        }
        if (board->black_knight & and) {
            string[i] = "n";
        }
        if (board->black_bishop & and) {
            string[i] = "b";
        }
        if (board->black_pawn & and) {
            string[i] = "p";
        }
    }

    return string;
}
