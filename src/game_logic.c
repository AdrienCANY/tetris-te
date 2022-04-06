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
    logic -> queue = malloc( queue_size * sizeof(Tetrimino*) );
    logic -> queue_size = 3;
    logic->hold_allowed = 1;

    // fill tetrimino queue

    for(int i = 0 ; i < logic->queue_size ; ++i)
    {
        logic -> queue[i] = TTMN_CreateRand(0,0);
    }

    // other properties

    logic->score = 0;
    logic->level = 1;
    logic->lines = 0;
    logic->seed = seed;

    // variable for other struct to know if the grid has been updated

    logic->grid_updated = 0;

    // properties for tetrimino's fall
    logic->dY = 0;
    logic->soft_dropping = 0;
    logic->speed = 1;
    logic->soft_drop_speed = 8;
    logic->timer = Timer_Create();
    Timer_Start(logic->timer);

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
        printf("Vertical collision detected !!\n");

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

    Timer_Destroy(logic->timer);

    free(logic);
    logic = NULL;
}

int GL_CheckWallCollision(GameLogic *logic)
{
    Tetrimino* ttmn = logic->player->ttmn; 

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        int x = ttmn->x + ttmn->tiles[i].x;
        int y = ttmn->y + ttmn->tiles[i].y;

        int left = x < 0 || y < 0;
        int right = x >= logic->grid->columns || y >= logic->grid->rows;

        if( left || right )
            return 1;
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
    

    // update grid

    int updated_rows[4];
    int* ptr = updated_rows;
    for(int i = 0 ; i < 4 ; updated_rows[i++] = -1);

    for(int i = 0 ; i < ttmn->tiles_count ; ++i)
    {
        int x = ttmn->x + ttmn->tiles[i].x;
        int y = ttmn->y + ttmn->tiles[i].y;
        Grid_SetTileColor(grid, x, y, ttmn->color);
        
        //check if the row 
        if( ! in(y, updated_rows, 4) )
            *ptr++ = y; 
    }

    // print in stdout updated rows
    for(int i = 0 ; i < 4 ; ++i)
    {
        printf("updated_rows[%d] = %d\n", i, updated_rows[i]);
    }

    // remove completed lines

    for(int i = 0 ; i < 4 ; ++i)
    {
        int row = updated_rows[i];
        if(row < 0)
            break;
        
        printf("checking for completion line n°%d\n", row);
        int completed = 1;

        // check if the line is completed

        for(int col = 0 ; col < grid->columns ; col++)
        {
            if(Grid_GetTileColor(grid, col, row) == TILE_BLACK)
            {
                completed = 0;
                break;
            }
        }

        // if completed, collapse top rows onto it

        if( completed )
        {
            printf("Removing line n°%d (completed)\n", row);

            // collapse top rows
            for(int top_row = row-1 ; top_row >= 0 ; top_row--)
            {
                for(int col = 0 ; col < grid->columns ; col ++)
                {
                    Grid_SetTileColor(grid, col, top_row+1, Grid_GetTileColor(grid, col, top_row));
                }
            }

            // create new blank first row
            for(int col = 0 ; col < grid->columns ; col++)
            {
                Grid_SetTileColor(grid, col, 0, TILE_BLACK);
            }
        }
    }

    // notify that the grid has been updated 

    logic->grid_updated = 1;

    // pop queue's first ttmn into play, and update rest of the queue

    GL_PopQueue(logic);

    // re-allow user to hold

    logic->hold_allowed = 1;

}

void GL_Update(GameLogic *gl)
{
    int speed = (gl->soft_dropping ? max(gl->soft_drop_speed, gl->speed) : gl->speed);
    gl->dY += speed * Timer_GetTicks(gl->timer) * (gl->soft_dropping ? 5 : 1 ) ;
    
    Timer_Start(gl->timer);

    GL_MovePlayer(gl, 0, gl->dY / 1000);

    gl->dY %= 1000;
}

void GL_HoldTTMN(GameLogic *logic)
{
    if( !logic->hold_allowed )
    {
        printf("You can not hold now !\n");
        return;
    }
    
    

    if(logic->hold == NULL)
    {

        // hold current ttmn
        logic->hold = malloc(sizeof(Tetrimino));
        memcpy(logic->hold, logic->player->ttmn, sizeof(Tetrimino));

        // load queue's next
        GL_PopQueue(logic);
    }
    else 
    {
        // switch currently held ttmn and current one
        Tetrimino* temp = logic->hold;
        logic->hold = logic->player->ttmn;
        logic->player->ttmn = temp;
        logic->player->ttmn->x = 0;
        logic->player->ttmn->y = 0;
    }
    
    logic->hold_allowed = 0;
}

void GL_PopQueue(GameLogic *logic)
{
    // pop the queue's first tetrimino into play

    Player_Load(logic->player, logic->queue[0]);

    // shift all tetriminos in the queue by 1 to the left

    for(int i = 1 ; i < logic->queue_size ; ++i)
    {
        logic->queue[i-1] = logic->queue[i];
    }

    // add a new tetrimino to the queue

    logic->queue[logic->queue_size - 1] = TTMN_CreateRand(0,0);
}

void GL_StartSoftDrop(GameLogic* logic)
{
    logic->soft_dropping = 1;    
}

void GL_StopSoftDrop(GameLogic* logic)
{
    logic->soft_dropping = 0;
}

void GL_HardDrop(GameLogic* logic)
{
    // to do après implémentation du ghost
}