#include <stdio.h>

#define SIZE 6
#define EMPTY 0
#define XVAL  1
#define OVAL  2

int grid[SIZE][SIZE] = {
    {1,1,0,2,0,0},
    {0,0,2,0,0,1},
    {0,1,1,0,2,0},
    {0,0,0,0,0,0},
    {2,0,0,1,2,1},
    {2,0,1,0,1,0}
};


void displayGrid() {
    int i, j;
    printf("\n   ");
    for (j = 0; j < SIZE; j++)
        printf("%d ", j);
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d  ", i);
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == XVAL)
                printf("X ");
            else if (grid[i][j] == OVAL)
                printf("O ");
            else
                printf(". ");
        }
        printf("\n");
    }
}


int checkTriple() {
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE - 2; j++)
            if (grid[i][j] != EMPTY &&
                grid[i][j] == grid[i][j+1] &&
                grid[i][j] == grid[i][j+2])
                return 0;

    for (j = 0; j < SIZE; j++)
        for (i = 0; i < SIZE - 2; i++)
            if (grid[i][j] != EMPTY &&
                grid[i][j] == grid[i+1][j] &&
                grid[i][j] == grid[i+2][j])
                return 0;

    return 1;
}


int checkBalance() {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        int x = 0, o = 0;
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == XVAL) x++;
            if (grid[i][j] == OVAL) o++;
        }
        if (x > 3 || o > 3) return 0;
    }

    for (j = 0; j < SIZE; j++) {
        int x = 0, o = 0;
        for (i = 0; i < SIZE; i++) {
            if (grid[i][j] == XVAL) x++;
            if (grid[i][j] == OVAL) o++;
        }
        if (x > 3 || o > 3) return 0;
    }

    return 1;
}


int isComplete() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (grid[i][j] == EMPTY)
                return 0;
    return 1;
}

int main() {
    int row, col;
    char choice;

    printf("=== SIMPLE TANGO GAME (6x6) ===\n");
    printf("Rules:\n");
    printf("1. No more than 2 same symbols together\n");
    printf("2. Each row and column must have equal X and O\n\n");

    while (1) {
        displayGrid();

        if (isComplete() && checkTriple() && checkBalance()) {
            printf("\nCONGRATULATIONS! YOU SOLVED THE PUZZLE\n");
            break;
        }

        printf("\nEnter row (0-5) and column (0-5): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid position!\n");
            continue;
        }

        printf("Enter X or O (or . to clear): ");
        scanf(" %c", &choice);

        int backup = grid[row][col];

        if (choice == 'X' || choice == 'x')
            grid[row][col] = XVAL;
        else if (choice == 'O' || choice == 'o')
            grid[row][col] = OVAL;
        else
            grid[row][col] = EMPTY;

        if (!checkTriple() || !checkBalance()) {
            printf("Invalid move! Rule violated.\n");
            grid[row][col] = backup;
        }
    }

    return 0;
}
