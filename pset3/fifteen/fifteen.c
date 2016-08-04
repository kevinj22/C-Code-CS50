/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// create initial blank position array
int blankpos[2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    blankpos[0] = d-1;
    blankpos[1] = d-1;
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int k = 1;
    for (int i = 0; i < d; i++ )
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j]=((d*d)-k);
            k++;
        }    
    }
    if ((((d*d)-1) % 2) != 0)
    {
        int t = board[d-1][d-3];
        board[d-1][d-3] = board[d-1][d-2];
        board[d-1][d-2] = t;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++ )
    {
        for (int j = 0; j < d; j++)
        {
            // need to update to change 0 to _
            if (board[i][j] == 0)
            {
                printf(" _ ");    
            }
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // blankpos is a global variable 
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                int tilepos[2] ={i,j};
                //printf("i:%i, j:%i, %i,%i\n",i,j,tilepos[0],tilepos[1]);
                //printf("i:%i, j:%i, %i,%i\n",i,j,blankpos[0],blankpos[1]);
                // check for diagonal move either same sum or sum + 2  / -2 depending on position of blank tile, and check if distance is greater than 1 apart
                // if so no move
                if ((abs(tilepos[0]-blankpos[0]) > 1 || abs(tilepos[1]-blankpos[1]) > 1) || ((tilepos[0] + tilepos[1]) == (blankpos[0] + blankpos[1])) || ((tilepos[0] + tilepos[1]) + 2) == (blankpos[0] + blankpos[1]) || ((tilepos[0] + tilepos[1]) - 2) == (blankpos[0] + blankpos[1]))
                {
                    //printf("%i\n",abs(tilepos[0]-blankpos[0]));
                    //printf("%i\n",abs(tilepos[1]-blankpos[1]));
                    return false;
                }
                else
                {
                    board[blankpos[0]][blankpos[1]] = board[tilepos[0]][tilepos[1]];
                    board[tilepos[0]][tilepos[1]] = 0;
                    blankpos[0]=tilepos[0];
                    blankpos[1]=tilepos[1];
                    return true;
                }
            }
        }
    }
   return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == d-1 && j == d-1 && board[i][j] == 0)
            {
                counter++;
            }
            else if (board[i][j] == counter)
            {
                counter++;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}
