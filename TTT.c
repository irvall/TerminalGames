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

void print_board()
{
    printf("\n");
    for (int i = 0; i < total; i++)
    {
        printf("|%c", *(board + i));
        if ((i + 1) % n == 0)
            printf("|\n");
    }
    printf("\n");
}

void print_debug()
{
    for (int i = 0; i < total; i++)
    {
        if (*(board + i) == empty)
            printf("- ");
        else
            printf("(%i %c) ", i, *(board + i));
    }
    printf("\n");
}

int search_winner()
{
    int c = 0;
    for (int i = 0; i < total; i += (n + 1))
    {
        int j = i + n + 1;
        if (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            if (++c == goal - 1)
                return 1;
        }
        else
            c = 0;
    }

    c = 0;
    for (int i = n - 1; i < total - m; i += (n / 2) + 1)
    {
        int j = i + (n / 2) + 1;
        if (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            if (++c == goal - 1)
                return 1;
        }
        else
            c = 0;
    }

    for (int i = 0; i < total; i++)
    {
        c = 0;
        int j = i + n;
        int temp = i;
        while (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + n;
            if (++c == goal - 1)
                return 1;
        }
        i = temp;
    }

    for (int i = 0; i < total - goal; i++)
    {
        c = 0;
        int j = i + 1;
        int temp = i;
        while (*(board + i) == *(board + j) && *(board + i) != empty && i % m == j % m - 1)
        {
            i = j;
            j = i + 1;
            if (++c == goal - 1)
                return 1;
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
    int i = y * n + x;
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
            nmoves++;
            switch_turn();
            return 1;
        }
    }
}

void make_random_move()
{
    int xr = rand() % m;
    int yr = rand() % n;
    if (!place(xr, yr))
        make_random_move();
}

int main()
{
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
        printf("Enter move (x,y): ");
        if (scanf("%d,%d", &x, &y))
        {
            if (!place(--x, --y))
            {
                printf("Illegal move!\n");
                continue;
            }
            print_board();
        }
        if (search_winner())
        {
            switch_turn();
            break;
        }
        if (gamemode == 1)
        {
            printf("\n...thinking...\n");
            sleep(1);
            make_random_move();
            print_board();
            if (search_winner())
            {
                switch_turn();
                break;
            }
        }
        if (nmoves == total - 1)
        {
            printf("Draw!\n");
            return EXIT_SUCCESS;
        }
    }
    printf("Game over!\n'%c' wins!\n", xo);
    return EXIT_SUCCESS;
}