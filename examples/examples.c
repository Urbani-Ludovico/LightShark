
#include <stdio.h>

#include "create.h"

int main() {
    printf("Available examples:\n(1) Board creation\n");

    printf("\nExample number: ");
    int example_number;
    scanf("%d", &example_number);

    int result;
    switch (example_number) {
        case 1:
            result = example_create();
            break;
        default:
            result = 0;
    }

    return result;
}