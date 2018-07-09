#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char empty = ' ';
int total;
int m;
int n;
int goal;
int gameover;
int gamemode;
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
    printf("\n");
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
    for (int i = n - 1; i < total-m; i += (n / 2) + 1)
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
            {
                gameover = 1;
                break;
            }
        }
        i = temp;
    }

    for (int i = 0; i < total; i += goal)
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

//Primitive computer AI
void make_random_move() 
{
    int xr = rand() % m;
    int yr = rand() % n;
    if(place(xr,yr) == 0)
        make_random_move();
}

int main()
{
    srand(time(NULL));
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
            if(!place(--x, --y)) {
                printf("Illegal move!\n");
                continue;
            }
            print_board();
            search_winner();
        }
        if(nmoves == total-1) {
            printf("Draw!\n");
            return EXIT_SUCCESS;
        }
    }
    printf("Game over!\n'%c' wins!\n", xo);
    return EXIT_SUCCESS;
}