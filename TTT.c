#include <stdio.h>
#include <stdlib.h>

const char empty = ' ';
int total;
int m;
int n;
int goal;
int gameover;
int nmoves;
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

void search_winner()
{
    int c = 0;
    //upper left to lower right diagonal
    for (int i = 0; i < total; i += (n + 1))
    {
        int j = i + n + 1;
        if (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            if (++c == goal - 1)
            {
                gameover = 1;
                break;
            }
        }
        else
            c = 0;
    }

    c = 0;
    //lower left to upper right diagonal
    for (int i = n - 1; i < total; i += (n / 2) + 1)
    {
        int j = i + (n / 2) + 1;
        if (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            if (++c == goal - 1)
            {
                gameover = 1;
                break;
            }
        }
        else
            c = 0;
    }

    for (int i = 0; i <= m; i++)
    {
        c = 0;
        int j = i + n;
        int temp = i;
        while (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + m;
            if (++c == goal - 1)
            {
                gameover = 1;
                break;
            }
        }
        i = temp;
    }

    for (int i = 0; i < total; i += m)
    {
        c = 0;
        int j = i + 1;
        int temp = i;
        while (*(board + i) == *(board + j) && *(board + i) != empty)
        {
            i = j;
            j = i + 1;
            if (++c == goal - 1)
            {
                gameover = 1;
                break;
            }
        }
        i = temp;
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
    nmoves++;
    switch_turn();
    return 1;
}

int main()
{
    xo = 'O';
    gameover = 0;
    nmoves = 0;
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
        printf("Enter move (x,y): ");
        if (scanf("%d,%d", &x, &y))
        {
            place(--x, --y);
            print_board();
            search_winner();
        }
        else return EXIT_FAILURE;
    }
    switch_turn();
    printf("Game over!\n'%c' wins!\n", xo);
    return EXIT_SUCCESS;
}