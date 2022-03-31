#include "game_logic.h"
#include "tetrimino.h"


GameLogic* GL_Create(int grid_rows, int grid_columns, int queue_size, int seed)
{
    GameLogic* logic = malloc(sizeof(GameLogic));


    // seed random number generator for Tetrimino creation
    srand(seed);

    // set properties

    logic->grid = Grid_Create(grid_rows, grid_columns);
    
    Tetrimino* ttmn = TTMN_CreateRand(0, 0);
    logic->player = Player_Create(ttmn);
    logic->hold = NULL;
    logic -> queue = calloc( queue_size, sizeof(Tetrimino*) );

    logic->score = 0;
    logic->level = 1;
    logic->lines = 0;
    logic->seed = seed;

    // variable for the renderer to know if the grid has been updated, ie if a TTMN has been placed

    logic->grid_updated = 0;

    return logic;
}

void GL_MovePlayer(GameLogic *gl, int dx, int dy)
{
    TTMN_Move(gl->player->ttmn, dx, dy);
}

void GL_Destroy(GameLogic *logic)
{
    // remove every tetriminos in the queue
    for(int  i = 0 ; i < logic->queue_size ; ++i)
    {   
        if(logic->queue[i] != NULL)
            TTMN_Destroy(logic->queue[i]);
    }

    // destroy properties
    free(logic->queue);
    Player_Destroy(logic->player);
    Grid_Destroy(logic->grid);
    if(logic -> hold != NULL)
        TTMN_Destroy(logic->hold);

    free(logic);
    logic = NULL;
}