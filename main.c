#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 16

struct Player {
    char name[20];
    char type; // 'H' = Human, 'C' = Computer
};

// Function to implement one round of the game
int game(char p1, char p2) {
    if (p1 == p2) return -1;
    if (p1 == 's' && p2 == 'p') return 0;
    else if (p1 == 'p' && p2 == 's') return 1;
    if (p1 == 's' && p2 == 'z') return 1;
    else if (p1 == 'z' && p2 == 's') return 0;
    if (p1 == 'p' && p2 == 'z') return 0;
    else if (p1 == 'z' && p2 == 'p') return 1;
}

char computerMove() {
    int n = rand() % 3;
    if (n == 0) return 's';
    else if (n == 1) return 'p';
    else return 'z';
}

void saveToScoreboard(const char* mode, const char* player1, const char* player2, const char* winner) {
    FILE *fptr = fopen("scoreboard.txt", "a");

    if (fptr == NULL) {
        printf("Error opening scoreboard.txt!\n");
        return;
    }

    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = 0; // Remove newline

    fprintf(fptr, "[%s] Mode: %s | %s vs %s | Winner: %s\n", timestamp, mode, player1, player2, winner);
    fclose(fptr);
}

int selectMode() {
    int choice;
    printf("Choose Game Mode:\n");
    printf("1. Player vs Computer (PvC)\n");
    printf("2. Player vs Player (PvP)\n");
    printf("3. Tournament Mode (Best of N rounds)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    return choice;
}

void printChoice(char c) {
    if (c == 's') printf("Stone");
    else if (c == 'p') printf("Paper");
    else if (c == 'z') printf("Scissors");
}

void pvpMode() {
    char p1, p2, winner[10], p1name[10], p2name[10];

    printf("Enter Player 1 name: ");
    scanf(" %s", p1name);
    printf("Enter Player 2 name: ");
    scanf(" %s", p2name);

    printf("%s - Enter s (STONE), p (PAPER), or z (SCISSOR): ", p1name);
    scanf(" %c", &p1);
    printf("%s - Enter s (STONE), p (PAPER), or z (SCISSOR): ", p2name);
    scanf(" %c", &p2);

    int result = game(p1, p2);

    if (result == -1) {
        printf("It's a draw!\n");
        strcpy(winner, "Draw");
    } else if (result == 1) {
        printf("%s wins!\n", p1name);
        strcpy(winner, p1name);
    } else {
        printf("%s wins!\n", p2name);
        strcpy(winner, p2name);
    }

    saveToScoreboard("PvP", p1name, p2name, winner);
}

void tournamentMode() {
    srand(time(NULL));
    int hCount, cCount;

    // Input validation
    printf("Enter number of human players (max %d): ", MAX_PLAYERS);
    scanf("%d", &hCount);
    printf("Enter number of computer players (max %d): ", MAX_PLAYERS - hCount);
    scanf("%d", &cCount);

    if (hCount < 0 || cCount < 0 || hCount + cCount > MAX_PLAYERS || hCount + cCount < 2) {
        printf("Invalid number of players. Total must be between 2 and %d.\n", MAX_PLAYERS);
        return;
    }

    struct Player players[MAX_PLAYERS];

    // Register human players
    for (int i = 0; i < hCount; i++) {
        printf("Enter name of Player %d: ", i + 1);
        scanf(" %s", players[i].name);
        players[i].type = 'H';
    }

    // Register computer players
    for (int i = 0; i < cCount; i++) {
        sprintf(players[hCount + i].name, "Computer%d", i + 1);
        players[hCount + i].type = 'C';
    }

    int round = 1;
    int currentPlayers = hCount + cCount;

    while (currentPlayers > 1) {
        printf("\n=== Round %d ===\n", round);
        int index = 0;

        for (int i = 0; i < currentPlayers; i += 2) {
            if (i + 1 >= currentPlayers) {
                // Odd player advances automatically
                printf("%s gets a bye!\n", players[i].name);
                players[index++] = players[i];
                continue;
            }

            char move1, move2;
            printf("\nMatch: %s vs %s\n", players[i].name, players[i + 1].name);

            // Player 1 move
            do {
                printf("%s - Enter s (STONE), p (PAPER), or z (SCISSOR): ", players[i].name);
                scanf(" %c", &move1);
            } while (move1 != 's' && move1 != 'p' && move1 != 'z');

            // Player 2 move
            do {
                printf("%s - Enter s (STONE), p (PAPER), or z (SCISSOR): ", players[i + 1].name);
                scanf(" %c", &move2);
            } while (move2 != 's' && move2 != 'p' && move2 != 'z');

            int result = game(move1, move2);
            if (result == -1) {
                printf("It's a draw! %s advances by default.\n", players[i].name);
                saveToScoreboard("Tournament", players[i].name, players[i + 1].name, players[i].name);
                players[index++] = players[i];
            } else if (result == 1) {
                printf("%s wins!\n", players[i].name);
                saveToScoreboard("Tournament", players[i].name, players[i + 1].name, players[i].name);
                players[index++] = players[i];
            } else {
                printf("%s wins!\n", players[i + 1].name);
                saveToScoreboard("Tournament", players[i].name, players[i + 1].name, players[i + 1].name);
                players[index++] = players[i + 1];
            }
        }

        currentPlayers = index;
        round++;
    }

    printf("\n🏆 Tournament Winner: %s 🏆\n", players[0].name);
    saveToScoreboard("Tournament Final", players[0].name, "N/A", players[0].name);
}

// Function to show recent games
#define MAX_HISTORY 5
#define MAX_LINE 256

void showRecentGames() {
    FILE *fp = fopen("scoreboard.txt", "r");
    if (fp == NULL) {
        printf("No previous game history found.\n\n");
        return;
    }

    char *lines[MAX_HISTORY];
    for (int i = 0; i < MAX_HISTORY; i++) {
        lines[i] = NULL;
    }

    char buffer[MAX_LINE];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (lines[count % MAX_HISTORY] != NULL) {
            free(lines[count % MAX_HISTORY]);
        }
        lines[count % MAX_HISTORY] = strdup(buffer);
        count++;
    }

    printf("\n======= Recent Matches (Last %d) =======\n", MAX_HISTORY);
    int start = count > MAX_HISTORY ? count - MAX_HISTORY : 0;
    for (int i = 0; i < MAX_HISTORY; i++) {
        int idx = (start + i) % MAX_HISTORY;
        if (lines[idx]) {
            printf("%s", lines[idx]);
            free(lines[idx]);  // Cleanup
        }
    }
    printf("========================================\n\n");

    fclose(fp);
}

// Main Game
int main() {
    srand(time(NULL));
    showRecentGames(); // Optional

    int mode = selectMode();

    if (mode == 1) {
        // PvC Mode (your original logic)
        char you, computer;
        int n = rand() % 100;
        if (n < 33) computer = 's';
        else if (n < 66) computer = 'p';
        else computer = 'z';

        printf("Enter s for STONE, p for PAPER, z for SCISSOR: ");
        scanf(" %c", &you);

        int result = game(you, computer);
        if (result == -1) printf("Game Draw!\n");
        else if (result == 1) printf("You won!\n");
        else printf("You lost!\n");

        printf("You: %c | Computer: %c\n", you, computer);

    } else if (mode == 2) {
        pvpMode();
    } else if (mode == 3) {
        tournamentMode();
    } else {
        printf("Invalid option!\n");
    }

    return 0;
}
