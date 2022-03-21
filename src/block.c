#include "block.h"
#include <stdlib.h>

Block* Block_Create(int x, int y, BlockColor color)
{
    Block *block = malloc(sizeof(Block));
    
    block->color = color;
    block->x = x;
    block->y = y;
    
    return block;
}

void Block_Destroy(Block *block)
{
    free(block);
    block = NULL;
}