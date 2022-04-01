#include "game_logic.h"
#include "tetrimino.h"
#include <stdio.h>
#include "utils.h"

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
    // horizontal movement

    TTMN_Move(gl->player->ttmn, dx, 0);
    if( GL_CheckWallCollision(gl) || GL_CheckTileCollision(gl) )
    {
        TTMN_Move(gl->player->ttmn, - dx, 0);
        printf("Horizontal collision detected !!\n");        
    }


    // vertical movement

    TTMN_Move(gl->player->ttmn, 0, dy);
    if( GL_CheckWallCollision(gl) || GL_CheckTileCollision(gl) )
    {
        TTMN_Move(gl->player->ttmn, 0, - dy);
        // printf("Vertical collision detected !!\n");

        GL_PlaceTTMN(gl);
    }


}

void GL_RotatePlayer(GameLogic *gl, int clockwise)
{
    TTMN_Rotate(gl->player->ttmn, clockwise);
    if(GL_CheckWallCollision(gl))
    {
        TTMN_Rotate(gl->player->ttmn, !clockwise);
    }
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

int GL_CheckWallCollision(GameLogic *logic)
{
    Tetrimino* ttmn = logic->player->ttmn; 

    if (ttmn->x < 0 || ttmn->y < 0)
        return 1;

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        int x = ttmn->x + ttmn->tiles[i].x;
        int y = ttmn->y + ttmn->tiles[i].y;

        if(x >= logic->grid->columns || y >= logic->grid->rows)
        {
            return 1;
        }
    }

    return 0;
}

int GL_CheckTileCollision(GameLogic *logic)
{
    Tetrimino *ttmn = logic->player->ttmn;
    Grid* grid = logic->grid;

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        int x = ttmn->x + ttmn->tiles[i].x;
        int y = ttmn->y + ttmn->tiles[i].y;
        TileColor color = Grid_GetTileColor(logic->grid, x, y);

        if( color != TILE_BLACK )
            return 1;
    }

    return 0;
}

void GL_PlaceTTMN(GameLogic *logic)
{
    Tetrimino* ttmn = logic->player->ttmn;
    Grid* grid = logic->grid;

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        int x = ttmn->x + ttmn->tiles[i].x;
        int y = ttmn->y + ttmn->tiles[i].y;
        Grid_SetTileColor(grid, x, y, ttmn->color);
    }

    logic->grid_updated = 1;

    Player_Load(logic->player, TTMN_CreateRand(0, 0));
}

void GL_Update(GameLogic *gl)
{
    // todo
}