#ifndef BLOCK_H_
#define BLOCK_H_

typedef enum
{
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_PURPLE,
    COLOR_ORANGE,
    COLOR_BLUE,
    COLOR_RED,
    COLOR_GREEN
} BlockColor;

typedef struct 
{
    int x, y;
    BlockColor color;
} Block;

Block* Block_Create(int x, int y, BlockColor color);
void Block_Destroy(Block* block);

#endif