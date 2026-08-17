#include <stdio.h>
#include <stdlib.h>

char board[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_title(void) {
    printf("\n\t\t Tic Tac Toe\n");
    printf("\t\t-------------\n");
}

void print_symbols(void) {
    printf("Player 1: 'X'  |  Player 2: 'O'\n\n");
}

void display_board(void) {
    printf("\t\t|---|---|---|\n");
    printf("\t\t| %c | %c | %c |\n", board[1], board[2], board[3]);
    printf("\t\t|---|---|---|\n");
    printf("\t\t| %c | %c | %c |\n", board[4], board[5], board[6]);
    printf("\t\t|---|---|---|\n");
    printf("\t\t| %c | %c | %c |\n", board[7], board[8], board[9]);
    printf("\t\t|---|---|---|\n\n");
}

int check_winner(void) {
    // Horizontal wins
    if (board[1] == board[2] && board[2] == board[3]) return 1;
    if (board[4] == board[5] && board[5] == board[6]) return 1;
    if (board[7] == board[8] && board[8] == board[9]) return 1;

    // Vertical wins
    if (board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[3] == board[6] && board[6] == board[9]) return 1;

    // Diagonal wins
    if (board[1] == board[5] && board[5] == board[9]) return 1;
    if (board[3] == board[5] && board[5] == board[7]) return 1;

    // Check for draw
    for (int i = 1; i <= 9; i++) {
        if (board[i] == (char)(i + '0')) {
            return -1; // Game still going
        }
    }

    return 0; // Game is a draw
}

int main(void) {
    int player = 1;
    int choice;
    int status = -1;
    char mark;

    do {
        clear_screen();
        print_title();
        print_symbols();
        display_board();

        player = (player % 2 != 0) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("Player %d (%c), enter a position (1-9): ", player, mark);
        if (scanf("%d", &choice) != 1) {
            // Clear invalid buffer input
            while (getchar() != '\n');
            continue;
        }

        if (choice >= 1 && choice <= 9 && board[choice] == (char)(choice + '0')) {
            board[choice] = mark;
            status = check_winner();
            if (status == -1) {
                player++;
            }
        } else {
            printf("\nInvalid move! Press Enter to try again...");
            while (getchar() != '\n');
            getchar();
        }
    } while (status == -1);

    clear_screen();
    print_title();
    print_symbols();
    display_board();

    if (status == 1) {
        printf(" ==> Congratulations! Player %d (%c) Wins!\n\n", player, mark);
    } else {
        printf(" ==> Game Over! It's a Draw.\n\n");
    }

    return 0;
}
