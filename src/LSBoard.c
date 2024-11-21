
#include "LSBoard.h"

ls_board_t ls_board_init() {
    return calloc(1, sizeof(struct _ls_board_t));
}

void ls_board_destroy(const ls_board_t board) {
    free(board);
}

void ls_board_print(const ls_board_t board) {
    char* string = ls_board_to_string(board);

    for (uint64_t row = 0; row < 8; row++) {
        for (uint64_t col = 0; col < 8; col++) {
            if (string[row * 8 + col] == 0) {
                printf(".");
            } else {
                printf("%c", string[row * 8 + col]);
            }
        }
        printf("\n");
    }

    free(string);
}

void ls_board_start(const ls_board_t board) {
    board->white_king = 0x8;
    board->white_queen = 0x10;
    board->white_rock = 0x81;
    board->white_knight = 0x42;
    board->white_bishop = 0x24;
    board->white_pawn = 0xff00;

    board->black_king = 0x800000000000000;
    board->black_queen = 0x1000000000000000;
    board->black_rock = 0x8100000000000000;
    board->black_knight = 0x4200000000000000;
    board->black_bishop = 0x2400000000000000;
    board->black_pawn = 0xff000000000000;
}

char* ls_board_to_string(const ls_board_t board) {
    const auto string = (char*)calloc(64, sizeof(char));

    for (uint8_t i = 0; i < 64; i++) {
        const uint64_t and = 1ULL << 63 - i;

        if (board->white_king & and) {
            string[i] = 'K';
        } else if (board->white_queen & and) {
            string[i] = 'Q';
        } else if (board->white_rock & and) {
            string[i] = 'R';
        } else if (board->white_knight & and) {
            string[i] = 'N';
        } else if (board->white_bishop & and) {
            string[i] = 'B';
        } else if (board->white_pawn & and) {
            string[i] = 'P';
        } else if (board->black_king & and) {
            string[i] = 'k';
        } else if (board->black_queen & and) {
            string[i] = 'q';
        } else if (board->black_rock & and) {
            string[i] = 'r';
        } else if (board->black_knight & and) {
            string[i] = 'n';
        } else if (board->black_bishop & and) {
            string[i] = 'b';
        } else if (board->black_pawn & and) {
            string[i] = 'p';
        }
    }

    return string;
}
