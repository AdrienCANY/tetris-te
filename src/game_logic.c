#include "game_logic.h"
#include "tetrimino.h"
#include <stdio.h>
#include "utils.h"
#include "constants.h"

GameLogic* GL_Create(int grid_rows, int grid_columns, int queue_size, int seed)
{
    GameLogic* logic = malloc(sizeof(GameLogic));

    // tetrimino's starting position

    logic->start_x = (grid_columns / 2) - 2;
    logic->start_y = 0;

    // set properties

    logic->grid = Grid_Create(grid_rows, grid_columns);
    
    // create player

    logic->player = Player_Create();
    
    // set hold
    
    logic->hold = NULL;

    // calloc tetrimino queue

    logic -> queue_size = GAME_QUEUE_SIZE;
    logic -> queue = calloc( sizeof(Tetrimino*), logic->queue_size );

    // other properties

    logic->seed = seed;

    // properties for tetrimino's fall

    logic->landing_shadow = malloc(sizeof(Tetrimino));

    // timer 

    logic->timer = Timer_Create();

    // event

    logic->event = NULL;
    logic->game_over = 0;

    // soft drop speed;

    logic->soft_drop_speed = 6;

    // init game

    GL_Init(logic);

    return logic;
}

void GL_Init(GameLogic* logic)
{
    // seed the random number generator

    srand(logic->seed);

    // reset grid 

    Grid_Clear(logic->grid);

    // load new tetrimino into play

    Tetrimino* player_ttmn = TTMN_CreateRand(logic->start_x, logic->start_y);
    Player_Load(logic->player, player_ttmn);

    // clear held tetrimino

    if(logic->hold != NULL)
    {
        TTMN_Destroy(logic->hold);
        logic->hold = NULL;
    }

    // fill tetrimino queue

    for(int i = 0 ; i < logic->queue_size ; ++i)
    {
        if(logic->queue[i] != NULL)
        {
            TTMN_Destroy(logic->queue[i]);
        }
        logic -> queue[i] = TTMN_CreateRand(logic->start_x,logic->start_y);
    }

    // landing shadow

    GL_UpdateLandingShadow(logic);

    // Timer

    Timer_Stop(logic->timer);

    // reset various variables
    logic->dY = 0;
    logic->soft_dropping = 0;
    logic->speed = 1;
    logic->score = 0;
    logic->level = 1;
    logic->lines = 0;
    logic->hold_allowed = 1;
    

}

void GL_MovePlayer(GameLogic *gl, int dx, int dy)
{
    Tetrimino* p_ttmn = gl->player->ttmn;

    // horizontal movement
    if(dx)
    {
        TTMN_Move(gl->player->ttmn, dx, 0);
        if( GL_CheckWallCollision(gl, p_ttmn) || GL_CheckTileCollision(gl, p_ttmn) )
        {
            TTMN_Move(gl->player->ttmn, - dx, 0);
            printf("Horizontal collision detected !!\n");        
        }
        GL_UpdateLandingShadow(gl);
    }

    // vertical movement

    if(dy)
    {
        TTMN_Move(gl->player->ttmn, 0, dy);
        if( GL_CheckWallCollision(gl, p_ttmn) || GL_CheckTileCollision(gl, p_ttmn) )
        {
            TTMN_Move(gl->player->ttmn, 0, - dy);
            printf("Vertical collision detected !!\n");

            GL_PlaceTTMN(gl);
        }
    }

}

void GL_RotatePlayer(GameLogic *gl, int clockwise)
{
    TTMN_Rotate(gl->player->ttmn, clockwise);
    if(GL_CheckWallCollision(gl, gl->player->ttmn))
    {
        TTMN_Rotate(gl->player->ttmn, !clockwise);
    }
    GL_UpdateLandingShadow(gl);
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

    if(logic->landing_shadow != NULL)
        TTMN_Destroy(logic->landing_shadow);

    if(logic->event != NULL)
        Event_Destroy(logic->event);

    free(logic);
    logic = NULL;
}

int GL_CheckWallCollision(GameLogic *logic, Tetrimino* ttmn)
{

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



int GL_CheckTileCollision(GameLogic *logic, Tetrimino *ttmn)
{
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

    // Create Event

    Event* event = GL_GetEvent(logic);
    event->type = EVENT_TETRIMINO_PLACED;

    
    // if ttmn is at its starting position, game over 
    if(ttmn->x == logic->start_x && ttmn->y == logic->start_y)
    {
        GL_GameOver(logic);
        event->type = EVENT_GAME_OVER;
    }

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

            event->type = EVENT_LINE_COMPLETED;
            event->ttmn = malloc(sizeof(Tetrimino));
            memcpy(event->ttmn, logic->player->ttmn, sizeof(Tetrimino));
            Event_AddData(event, row);

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

    // pop queue's first ttmn into play, and update rest of the queue

    if(!GL_IsGameOver(logic))
        GL_PopQueue(logic);

    // re-allow user to hold

    logic->hold_allowed = 1;

}

void GL_Update(GameLogic *gl)
{
    if(gl->timer->isStarted && !gl->timer->isPaused)
    {
        int speed = (gl->soft_dropping ? max(gl->soft_drop_speed, gl->speed) : gl->speed);
        gl->dY += speed * Timer_GetTicks(gl->timer) * (gl->soft_dropping ? 5 : 1 ) ;
        
        Timer_Start(gl->timer);

        GL_MovePlayer(gl, 0, gl->dY / 1000);

        gl->dY %= 1000;
    }

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
        logic->player->ttmn->x = logic->start_x;
        logic->player->ttmn->y = logic->start_y;
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

    logic->queue[logic->queue_size - 1] = TTMN_CreateRand(logic->start_x,logic->start_y);

    // update shadow
    GL_UpdateLandingShadow(logic);
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
    printf("hard dropping\n");
    logic->player->ttmn->y = logic->landing_shadow->y;
    GL_PlaceTTMN(logic);
}

void GL_UpdateLandingShadow(GameLogic *logic)
{
    // make a copy of player's tetrimino
    Tetrimino* shadow = logic->landing_shadow;
    Tetrimino* player = logic->player->ttmn;
    memcpy(shadow, player, sizeof(Tetrimino));
    shadow->color = TILE_GREY;

    while(!GL_CheckWallCollision(logic, shadow) && !GL_CheckTileCollision(logic, shadow))
    {
        shadow->y++;
    }
    shadow->y--;
}

Tetrimino* GL_GetLandingShadow(GameLogic* logic)
{
    return logic->landing_shadow;
}

int GL_IsStarted(GameLogic* logic)
{
    return logic->timer->isStarted;
}

void GL_Start(GameLogic *logic)
{
    // start timer
    printf("Starting game...\n");
    Timer_Start(logic->timer);
}

int GL_IsPaused(GameLogic *logic)
{
    return logic->timer->isPaused;
}

void GL_Resume(GameLogic* logic)
{
    printf("Resuming game...\n");
    Timer_Resume(logic->timer);
}

void GL_Pause(GameLogic *logic)
{
    printf("Pausing game...\n");
    
    Timer_Pause(logic->timer);
}

int GL_IsGameOver(GameLogic *logic)
{
    return logic->game_over;
}

void GL_Restart(GameLogic *logic)
{
    printf("Restarting game ...\n");

    Event* event = GL_GetEvent(logic);
    event->type = EVENT_GAME_RESTART;

    GL_Init(logic);
}

void GL_GameOver(GameLogic *logic)
{
    logic->game_over = 1;
    Timer_Stop(logic->timer);
}

Event* GL_GetEvent(GameLogic* logic)
{
    if(logic->event == NULL)
        logic->event = Event_CreateBlank();
    return logic->event;
}