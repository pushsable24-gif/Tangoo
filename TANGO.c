#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SIZE 6
#define EMPTY 0
#define XVAL  1
#define OVAL  2

#define WHITE  15
#define GREY   7
#define RED    12
#define YELLOW 14
#define CYAN   11

// ---------------- CONSOLE UTILS ----------------

void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD charsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coordScreen, &charsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coordScreen, &charsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// ---------------- GAME DATA ----------------

int grid[SIZE][SIZE] = {
    {1,0,0,2,0,0},
    {0,0,2,0,0,1},
    {0,1,1,0,2,0},
    {0,0,0,0,0,0},
    {2,0,0,1,2,1},
    {0,0,0,0,1,0}
};

int fixed[SIZE][SIZE];
int cr = 0, cc = 0;

// ---------------- RULE CHECKS ----------------

int checkTriple() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 2; j++)
            if (grid[i][j] &&
                grid[i][j] == grid[i][j+1] &&
                grid[i][j] == grid[i][j+2])
                return 0;

    for (int j = 0; j < SIZE; j++)
        for (int i = 0; i < SIZE - 2; i++)
            if (grid[i][j] &&
                grid[i][j] == grid[i+1][j] &&
                grid[i][j] == grid[i+2][j])
                return 0;

    return 1;
}

int checkBalance() {
    for (int i = 0; i < SIZE; i++) {
        int x = 0, o = 0;
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == XVAL) x++;
            if (grid[i][j] == OVAL) o++;
        }
        if (x > 3 || o > 3) return 0;
    }

    for (int j = 0; j < SIZE; j++) {
        int x = 0, o = 0;
        for (int i = 0; i < SIZE; i++) {
            if (grid[i][j] == XVAL) x++;
            if (grid[i][j] == OVAL) o++;
        }
        if (x > 3 || o > 3) return 0;
    }

    return 1;
}

int isComplete() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == EMPTY)
                return 0;
    return 1;
}

// ---------------- DISPLAY ----------------

void drawGrid() {
    clearScreen();
    setColor(WHITE);

    printf("=== TANGO GAME (6x6) ===\n");
    printf("WASD Move | X/O Place | SPACE Clear | Q Quit\n\n");

    for (int i = 0; i < SIZE; i++) {
        setColor(GREY);
        printf("  +---+---+---+---+---+---+\n");
        printf("%d |", i);

        for (int j = 0; j < SIZE; j++) {
            if (i == cr && j == cc) {
                setColor(RED);
                printf("[");
            } else {
                printf(" ");
            }

            if (grid[i][j] == XVAL) {
                setColor(YELLOW);
                printf("X");
            } else if (grid[i][j] == OVAL) {
                setColor(CYAN);
                printf("O");
            } else {
                printf(".");
            }

            if (i == cr && j == cc) {
                setColor(RED);
                printf("]");
            } else {
                printf(" ");
            }

            setColor(GREY);
            printf("|");
        }
        printf("\n");
    }

    printf("  +---+---+---+---+---+---+\n");
    setColor(WHITE);
}

// ---------------- MAIN ----------------

int main() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            fixed[i][j] = (grid[i][j] != EMPTY);

    char ch;

    while (1) {
        drawGrid();
        ch = getch();

        if (ch == 'q' || ch == 'Q')
            break;

        if (ch == 'w' && cr > 0) cr--;
        if (ch == 's' && cr < SIZE - 1) cr++;
        if (ch == 'a' && cc > 0) cc--;
        if (ch == 'd' && cc < SIZE - 1) cc++;

        if (!fixed[cr][cc]) {
            int backup = grid[cr][cc];

            if (ch == 'x' || ch == 'X') grid[cr][cc] = XVAL;
            if (ch == 'o' || ch == 'O') grid[cr][cc] = OVAL;
            if (ch == ' ') grid[cr][cc] = EMPTY;

            if (!checkTriple() || !checkBalance())
                grid[cr][cc] = backup;
        }

        if (isComplete() && checkTriple() && checkBalance()) {
            drawGrid();
            setColor(YELLOW);
            printf("\n🎉 CONGRATULATIONS! YOU SOLVED THE PUZZLE 🎉\n");
            setColor(WHITE);
            getch();
            break;
        }

        Sleep(15);   // smooth movement, no lag
    }

    setColor(WHITE);
    return 0;
}
