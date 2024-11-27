
#include "LSBoard.h"

#include "LSMoves.h"

#include <stdio.h>
#include <stdlib.h>

ls_board_t ls_board_init() {
    return calloc(1, sizeof(struct _ls_board_t));
}

ls_board_t ls_board_copy(ls_board_t const board) {
    auto const copy = (ls_board_t)malloc(sizeof(struct _ls_board_t));

    copy->white_king = board->white_king;
    copy->black_king = board->black_king;
    copy->white_queen = board->white_queen;
    copy->black_queen = board->black_queen;
    copy->white_bishop = board->white_bishop;
    copy->black_bishop = board->black_bishop;
    copy->white_knight = board->white_knight;
    copy->black_knight = board->black_knight;
    copy->white_rook = board->white_rook;
    copy->black_rook = board->black_rook;
    copy->white_pawn = board->white_pawn;
    copy->black_pawn = board->black_pawn;

    return copy;
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
    board->white_king = LS_START_POSITION_WHITE_KING;
    board->white_queen = LS_START_POSITION_WHITE_QUEEN;
    board->white_rook = LS_START_POSITION_WHITE_ROOK;
    board->white_knight = LS_START_POSITION_WHITE_KNIGHT;
    board->white_bishop = LS_START_POSITION_WHITE_BISHOP;
    board->white_pawn = LS_START_POSITION_WHITE_PAWN;

    board->black_king = LS_START_POSITION_BLACK_KING;
    board->black_queen = LS_START_POSITION_BLACK_QUEEN;
    board->black_rook = LS_START_POSITION_BLACK_ROCK;
    board->black_knight = LS_START_POSITION_BLACK_KNIGHT;
    board->black_bishop = LS_START_POSITION_BLACK_BISHOP;
    board->black_pawn = LS_START_POSITION_BLACK_PAWN;
}

char* ls_board_to_string(const ls_board_t board) {
    auto const string = (char*)calloc(64, sizeof(char));

    for (uint8_t i = 0; i < 64; i++) {
        const uint64_t and = 1ULL << (63 - i);

        if (board->white_king & and) {
            string[i] = 'K';
        } else if (board->white_queen & and) {
            string[i] = 'Q';
        } else if (board->white_rook & and) {
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
        } else if (board->black_rook & and) {
            string[i] = 'r';
        } else if (board->black_knight & and) {
            string[i] = 'n';
        } else if (board->black_bishop & and) {
            string[i] = 'b';
        } else if (board->black_pawn & and) {
            string[i] = 'p';
        } else {
            string[i] = ' ';
        }
    }

    return string;
}
