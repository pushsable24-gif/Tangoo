#include <stdio.h>

#define SIZE 6
#define EMPTY 0
#define XVAL  1
#define OVAL  2

//LEVELS
int level1[SIZE][SIZE] = {
    {1,1,0,2,0,0},
    {0,0,2,0,0,1},
    {0,1,1,0,2,0},
    {0,0,0,0,0,0},
    {2,0,0,1,2,1},
    {2,0,1,0,1,0}
};

int level2[SIZE][SIZE] = {
    {1,2,0,0,0,0},
    {2,0,2,0,0,1},
    {0,1,1,0,2,0},
    {0,0,0,0,0,0},
    {1,0,0,0,2,1},
    {2,0,1,0,1,0}
};

int level3[SIZE][SIZE] = {
    {2,1,0,1,0,0},
    {0,0,0,0,0,1},
    {0,1,1,0,0,0},
    {0,0,2,2,0,0},
    {2,0,0,0,0,1},
    {2,0,0,1,0,0}
};

int grid[SIZE][SIZE];

void loadLevel(int src[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            grid[i][j] = src[i][j];
}

// defining rows
void printLine() {
    int i;
    printf("  ");
    for (i = 0; i < SIZE; i++)
        printf("+---");
    printf("+\n");
}

// displaying grid
void displayGrid() {
    int i, j;

    printf("\n    ");
    for (j = 0; j < SIZE; j++)
        printf(" %d  ", j);
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printLine();
        printf("%d ", i);

        for (j = 0; j < SIZE; j++) {
            printf("| ");
            if (grid[i][j] == XVAL)
                printf("X ");
            else if (grid[i][j] == OVAL)
                printf("O ");
            else
                printf(". ");
        }
        printf("|\n");
    }
    printLine();
}

// checking conditions as per rules
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

// win conditions
int isComplete() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (grid[i][j] == EMPTY)
                return 0;
    return 1;
}

//main
int main() {
    int choice;
    int row, col;
    char symbol;

    printf("=== TANGO GAME (6x6) ===\n");
    printf("Select Level:\n");
    printf("1. EASY\n");
    printf("2. MEDIUM\n");
    printf("3. HARD\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Level 1: EASY\n");
            loadLevel(level1);
            break;

        case 2:
            printf("Level 2: MEDIUM\n");
            loadLevel(level2);
            break;

        case 3:
            printf("Level 3: HARD\n");
            loadLevel(level3);
            break;

        default:
            printf("Invalid choice! Defaulting to EASY.\n");
            loadLevel(level1);
    }

    while (1) {
        displayGrid();

        if (isComplete() && checkTriple() && checkBalance()) {
            printf("\n🎉 CONGRATULATIONS! YOU SOLVED THE PUZZLE 🎉\n");
            break;
        }

        printf("\nEnter row and column (0-5): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid position!\n");
            continue;
        }

        printf("Enter X or O (or . to clear): ");
        scanf(" %c", &symbol);

        int backup = grid[row][col];

        if (symbol == 'X' || symbol == 'x')
            grid[row][col] = XVAL;
        else if (symbol == 'O' || symbol == 'o')
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
