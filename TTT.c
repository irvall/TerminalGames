#include <stdio.h>
#include <stdlib.h>

const char empty = ' ';
int total;
int m;
int n;
int goal;
int gameover;
char xo;
char *board;

void print_board()
{
    for (int i = 0; i < total; i++)
    {
        printf("|%c", *(board + i));
        if ((i + 1) % m == 0)
            printf("|\n");
    }
}

//x - - - x - - - x

void search_winner()
{
    for (int i = 0; i < goal; i += (n + 1))
    {
        int j = i + n + 1;
        if (*(board + i) == *(board + j))
        {
            if (i == total - 1)
            {
                gameover = 1;
                break;
            }
        }
        else
            break;
    }
}

void switch_turn()
{
    xo = (xo == 'X') ? 'O' : 'X';
}

int place(int x, int y)
{
    int i = y * n + x;
    char *err = "Illegal move!\n";
    if (i >= total)
    {
        printf("%s", err);
        return 0;
    }
    else
    {
        char *p = board + i;
        if (*p != empty)
        {
            printf("%s", err);
            return 0;
        }
        else
        {
            *p = xo;
        }
    }
    switch_turn();
    return 1;
}

int main()
{
    xo = 'O';
    gameover = 0;
    printf("Enter dimensions (m,n): ");
    scanf("%d,%d", &m, &n);
    printf("Enter goal: ");
    scanf("%d", &goal);
    total = m * n;
    board = (char *)malloc(total * sizeof(char));
    for (int i = 0; i < total; i++)
        *(board + i) = empty;

    int x;
    int y;
    while (!gameover)
    {
        print_board();
        printf("Enter move (x,y): ");

        if (scanf("%d,%d", &x, &y))
        {
            place(--x, --y);
            search_winner();
        }
        else printf("Move should be formatted \'x,y\'\n");
    }

    printf("Game over!\n");

    return EXIT_SUCCESS;
}
