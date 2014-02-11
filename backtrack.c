#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE = 8;
int* queens;
int count = 0;

int checkRow(int y) {
    for(int i = 0; i < count; ++i) {
        if(queens[i*2+1] == y) return 0;
    }
    return 1;
}

int checkColumn(int x) {
    for(int i = 0; i < count; ++i) {
        if(queens[i*2] == x) return 0;
    }
    return 1;
}

int checkDiagonal(int x, int y) {
    for(int i = 0; i < count; ++i) {
        int qx = queens[i*2];
        int qy = queens[i*2+1];

        if((x - y == qx - qy) || (x + y == qx + qy)) {
            return 0;
        }
    }
    return 1;
}

void placeQueen(int x, int y) {
    queens[2*count+0] = x;
    queens[2*count+1] = y;
    count++;
}

void removeLastQueen() {
    count--;
}

int containsQueen(int x, int y) {
    for(int i = 0; i < count; ++i) {
        if(queens[i*2] == x && queens[i*2+1] == y) {
            return 1;
        }
    }
    return 0;
}

void printField() {
    printf("+"); for(int i = 0; i < SIZE; ++i) printf("-"); printf("+\n");
    for(int x = 0; x < SIZE; ++x) {
        printf("|");
        for(int y = 0; y < SIZE; ++y) {
            printf(containsQueen(x, y) ? "X" : " ");
        }
        printf("|\n");
    }
    printf("+"); for(int i = 0; i < SIZE; ++i) printf("-"); printf("+\n");
}

int next() {
    for(int x = 0; x < SIZE; ++x) {
        if(!checkColumn(x)) continue; // backtrack!

        for(int y = 0; y < SIZE; ++y) {
            if(!checkRow(y)) continue; // backtrack!

            if(checkDiagonal(x, y)) {
                placeQueen(x, y);
                if(count >= SIZE) {
                    return 1;
                }
                if(next()) {
                    return 1;
                }
                removeLastQueen(); // backtrack!
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    if(argc >= 2) {
        SIZE = atoi(argv[1]);
    }
    printf("Field size: %d\n", SIZE);

    queens = malloc(2 * SIZE * sizeof(int));

    clock_t start = clock();
    next();
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC * 1000;

    printf("Found solution in %.5f ms:\n", seconds);

    printField();
    free(queens);
    return 0;
}