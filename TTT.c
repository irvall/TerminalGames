#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const char empty = ' ';
int total;
int m;
int n;
int goal;
int gamemode;
int nmoves;
char xo;
char *board;

void print_debug()
{
    for (int i = 0; i < total; i++)
    {
        if (*(board + i) == empty)
            printf("- ");
        else
            printf("(%c %d)", *(board + i), i);
    }
    printf("\n");
}
void print_board()
{
    printf("\n");
    int k = 0;
    for (int i = 0; i < total; i++)
    {
        printf("|%c", *(board + i));
        if ((i + 1) % m == 0)
            printf("| %d\n", ++k);
    }

    for (int i = 0; i < m; i++)
    {
        if (i > 8)
            printf(" %d", (i + 1) / 10);
        else
            printf(" %d", i + 1);
    }
    printf("\n");
    k = 10;
    while (--k > 0)
        printf("  ");

    for (int i = 9; i < m; i++)
        printf(" %d", (i + 1) % 10);

    printf("\n");
}

int search_winner()
{
    int c;
    for (int i = 0; i < total; i++)
    {
        c = 0;
        int j = i + m + 1;
        int temp = i;
        while (i < total && j < total && i >= 0 && j >= 0 && *(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + m + 1;
            if (++c == goal - 1)
            {
                return 1;
            }
        }
        i = temp;
    }

    for (int i = m - 1; i < total - n; i++)
    {
        c = 0;
        int j = i + (m - 1);
        int temp = i;
        while (i < total - n && j < total - n && i >= 0 && j >= 0 && *(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + (m - 1);
            if (++c == goal - 1)
                return 1;
        }
        i = temp;
    }

    for (int i = 0; i < total; i++)
    {
        c = 0;
        int j = i + m;
        int temp = i;
        while (i < total && j < total && i >= 0 && j >= 0 && *(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + m;
            if (++c == goal - 1)
            {
                return 1;
            }
        }
        i = temp;
    }

    for (int i = 0; i <= total - goal; i++)
    {
        c = 0;
        int j = i + 1;
        int temp = i;
        while (i < total && j < total && i >= 0 && j >= 0 && *(board + i) == *(board + j) && *(board + i) != empty && i % n == (j % n) - 1)
        {
            i = j;
            j = i + 1;
            if (++c == goal - 1)
            {
                return 1;
            }
        }
        i = temp;
    }
    return 0;
}

void switch_turn()
{
    xo = (xo == 'X') ? 'O' : 'X';
}

int place(int x, int y)
{
    int i = y * m + x;
    if (i >= total)
    {
        return 0;
    }
    else
    {
        char *p = board + i;
        if (*p != empty)
        {
            return 0;
        }
        else
        {
            *p = xo;
        }
    }
    nmoves++;
    switch_turn();
    return 1;
}

void make_random_move()
{
    int xr = rand() % m;
    int yr = rand() % n;
    if (!place(xr, yr))
        make_random_move();
}

void print_think_message()
{
    printf("\n");
    char *messages[] = {"great move, let me think",
                        "holy moly, need to think",
                        "I'm winning now",
                        "you just wasted a move",
                        "thinking",
                        "hasta la vista, baby",
                        "GG",
                        "surrender now"};
    int r = rand() % 8;
    printf("...%s...\n", messages[r]);
}

void print_welcome()
{
    printf("%s\n%s\n%s\n\n",
           "_  _  _ _______        _______  _____  _______ _______",
           "|  |  | |______ |      |       |     | |  |  | |______",
           "|__|__| |______ |_____ |_____  |_____| |  |  | |______");
}

void print_illegal()
{
    printf("%s\n  %s\n%s\n\n",
           "_____               _______  ______ _______             _______  _____  _    _ _______",
           "|   |      |      |______ |  ____ |_____| |           |  |  | |     |  \\  /  |______",
           "__|__ |_____ |_____ |______ |_____| |     | |_____      |  |  | |_____|   \\/   |______");
}

void print_gameover()
{
    printf("%s\n%s\n%s\n\n",
           " ______ _______ _______ _______       _____  _    _ _______  ______",
           "|  ____ |_____| |  |  | |______      |     |  \\  /  |______ |_____/",
           "|_____| |     | |  |  | |______      |_____|   \\/   |______ |    \\_");
}

void print_youwon()
{
    printf("%s\n  %s\n   %s\n\n",
           "__   __  _____  _     _      _  _  _ _____ __   _",
           "\\_/   |     | |     |      |  |  |   |   | \\  |",
           "|    |_____| |_____|      |__|__| __|__ |  \\_|");
}

void print_draw()
{
    printf("%s\n%s\n%s\n\n",
           "______   ______ _______ _  _  _",
           "|     \\ |_____/ |_____| |  |  |",
           "|_____/ |    \\_ |     | |__|__|");
}

int main()
{
    print_welcome();
    xo = 'O';
    nmoves = 0;
    srand(time(NULL));
    printf("Enter dimensions (m,n): ");
    scanf("%d,%d", &m, &n);
    printf("Enter goal: ");
    scanf("%d", &goal);
    printf("Enter number of players: ");
    scanf("%d", &gamemode);
    total = m * n;
    board = (char *)malloc(total * sizeof(char));
    for (int i = 0; i < total; i++)
        *(board + i) = empty;

    int x;
    int y;
    while (2 + 2 == 4)
    {
	print_board();
        printf("Enter move (x,y): ");
	if (scanf("%d,%d", &x, &y))
        {
            if (!place(--x, --y))
            {
                print_illegal();
                continue;
            }
            print_board();
        }
        if (search_winner())
        {
            print_youwon();
            break;
        }
        if (gamemode == 1)
        {
            print_think_message();
            sleep(1);
            make_random_move();
            print_board();
            if (search_winner())
            {
                print_gameover();
                break;
            }
        }
        if (nmoves == total)
        {
            print_draw();
            break;
        }
    }
    free(board);
    return EXIT_SUCCESS;
}
