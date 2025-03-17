#include <stdio.h>
#include <pthread.h>

#define SIZE 9  // Sudoku grid size

int sudoku[SIZE][SIZE];  // 9x9 Sudoku grid
int flag = 1;

// Structure to pass row/col/grid indices to threads
typedef struct {
    int index;
} Parameters;

// Function to check if an array contains numbers 1-9 exactly once
int is_valid(int arr[]) {
    int vis[SIZE + 1] = {0}; // Array to track occurrences (0-9)
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < 1 || arr[i] > 9 || vis[arr[i]]) {
            return 0;
        }
        vis[arr[i]] = 1;
    }
    return 1;
}

// Check all rows
void* check_rows(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        flag &= is_valid(sudoku[i]);
    }
    pthread_exit(NULL);
}

// Check all columns
void* check_columns(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        int buk[SIZE];
        for (int j = 0; j < SIZE; j++) {
            buk[j] = sudoku[j][i];
        }
        flag &= is_valid(buk);
    }
    pthread_exit(NULL);
}

// Check a 3x3 sub-grid
void* check_subgrid(void* param) {
    Parameters* p = (Parameters*) param;
    int x = (p->index / 3) * 3;
    int y = (p->index % 3) * 3;
    int buk[SIZE], k = 0;
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            buk[k++] = sudoku[i][j];
        }
    }
    flag &= is_valid(buk);
    pthread_exit(NULL);
}

// Check main diagonal (top-left to bottom-right)
void* check_main_diagonal(void* arg) {
    int buk[SIZE];
    for (int i = 0; i < SIZE; i++) {
        buk[i] = sudoku[i][i];
    }
    flag &= is_valid(buk);
    pthread_exit(NULL);
}

// Check secondary diagonal (top-right to bottom-left)
void* check_secondary_diagonal(void* arg) {
    int buk[SIZE];
    for (int i = 0; i < SIZE; i++) {
        buk[i] = sudoku[i][SIZE - 1 - i];
    }
    flag &= is_valid(buk);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc == 0) {
        printf("You need to provide a sudoku data file!\n");
        printf("Usage:  sudoku  <filename>\n");
        return 1;
    }
    
    // Read Sudoku puzzle from file
    FILE* file = fopen(argv[1], "r");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, "%d,", &sudoku[i][j]);
        }
    }
    fclose(file);
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    pthread_t threads[13];
    Parameters params[9];

    // Create threads
    pthread_create(&threads[0], NULL, check_rows, NULL);
    pthread_create(&threads[1], NULL, check_columns, NULL);
    
    // Create threads for sub-grids
    for (int i = 0; i < 9; i++) {
        params[i].index = i;
        pthread_create(&threads[i + 2], NULL, check_subgrid, &params[i]);
    }

    // Create threads for diagonals
    pthread_create(&threads[11], NULL, check_main_diagonal, NULL);
    pthread_create(&threads[12], NULL, check_secondary_diagonal, NULL);

    // Join threads
    for (int i = 0; i < 13; i++) {
        pthread_join(threads[i], NULL);
    }

    if (flag) {
        printf("This sudoku solution is valid\n");
    } else {
        printf("invalid sudoku solution\n");
    }

    return 0;
}
