#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // For _kbhit and _getch [cite: 80]

#define WIDTH 80
#define HEIGHT 25

// Struct to hold state for easy saving/loading [cite: 58]
typedef struct {
    int score;
    int bombX, bombY;
    int planeX;
    int bombActive;
    int bombsDeactivated;
    int currentLen;
    char word[11];
} GameState;

// Global word list to make random selection easier
char dictionary[100][11];
int dictCount = 0;

// Function prototypes [cite: 89]
void initGame(GameState *g);
void loadDictionary();
void spawnBomb(GameState *g);
void draw(GameState *g);
void saveGame(GameState *g);
void loadGame(GameState *g);
void menu(GameState *g, int fromEsc);

// Loading the codewords.txt file [cite: 38]
void loadDictionary() {
    FILE *f = fopen("codewords.txt", "r");
    if (!f) return;
    while (fscanf(f, "%10s", dictionary[dictCount]) != EOF && dictCount < 100) {
        dictCount++;
    }
    fclose(f);
}

void initGame(GameState *g) {
    g->score = 0;
    g->planeX = 0;
    g->bombActive = 0;
    g->bombsDeactivated = 0;
    g->currentLen = 3; // Starts at 3 letters [cite: 39]
}

void spawnBomb(GameState *g) {
    g->bombX = g->planeX + 2;
    g->bombY = 2;
    g->bombActive = 1;

    // Pick a word that matches the current difficulty length
    int attempts = 0;
    while(attempts < 500) {
        int r = rand() % dictCount;
        if (strlen(dictionary[r]) == g->currentLen) {
            strcpy(g->word, dictionary[r]);
            break;
        }
        attempts++;
    }
}

void saveGame(GameState *g) {
    char filename[50];
    printf("\nEnter filename to save: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "wb");
    if (f) {
        fwrite(g, sizeof(GameState), 1, f);
        fclose(f);
        printf("Game saved!");
        Sleep(1000);
    }
}

void loadGame(GameState *g) {
    char filename[50];
    printf("\nEnter filename to load: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("No such file\n"); // Required error message [cite: 61]
        Sleep(1000);
        return;
    }
    fread(g, sizeof(GameState), 1, f);
    fclose(f);
}

void menu(GameState *g, int fromEsc) {
    while (1) {
        system("cls"); // [cite: 72]
        printf("--- TYPING OF THE BOMBS ---\n");
        printf("1. New Game\n2. Load a Saved Game\n3. Save Current Game\n");
        if (fromEsc) printf("4. Return to Game\n"); // 
        printf("5. Exit\n");

        char c = _getch();
        if (c == '1') { initGame(g); return; }
        if (c == '2') { loadGame(g); return; }
        if (c == '3') { saveGame(g); }
        if (c == '4' && fromEsc) return;
        if (c == '5') exit(0);
    }
}

int main() {
    srand(time(NULL));
    loadDictionary();
    GameState g;
    initGame(&g);
    menu(&g, 0);

    while (1) {
        // 1. Handle Input [cite: 74]
        if (_kbhit()) {
            char hit = _getch();
            if (hit == 27) { // ESC key [cite: 55]
                menu(&g, 1);
            } else if (g.bombActive) {
                if (hit == g.word[0]) {
                    g.score += 1; // 
                    memmove(g.word, g.word + 1, strlen(g.word)); // Shift code [cite: 34]
                    if (strlen(g.word) == 0) {
                        g.bombActive = 0;
                        g.bombsDeactivated++;
                        // Difficulty Logic [cite: 40, 42]
                        if (g.bombsDeactivated % 5 == 0 && g.currentLen < 10) {
                            g.currentLen++;
                        }
                    }
                } else {
                    g.score -= 1; // Mistyped penalty 
                }
            }
        }

        // 2. Game Physics
        g.planeX++;
        if (g.planeX > WIDTH - 10) g.planeX = 0; // Plane restarts at column 0 [cite: 25]

        if (!g.bombActive) {
            spawnBomb(&g);
        } else {
            g.bombY++; // Vertical drop [cite: 28]
            if (g.bombY >= HEIGHT - 2) { // Hit the city [cite: 44]
                system("cls");
                printf("\n\n   GAME OVER   \n\n"); // [cite: 45]
                printf("Restart? (y/n): ");
                char choice = _getch();
                if (choice == 'y') { initGame(&g); menu(&g, 0); }
                else exit(0);
            }
        }

        // 3. Render
        system("cls");
        printf("Score: %d\t\tDeactivated: %d\n", g.score, g.bombsDeactivated);
        
        // Simple positioning logic for visuals
        for(int i=0; i<g.bombY; i++) printf("\n");
        for(int j=0; j<g.bombX; j++) printf(" ");
        printf("<|> %s\n", g.word); // Bomb and code [cite: 21]
        
        Sleep(150); // Speed control
    }
    return 0;
}