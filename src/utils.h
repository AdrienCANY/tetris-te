#ifndef UTILS_H_
#define UTILS_H_

#include "tile_color.h"
#include "global.h"
#include "grid.h"

int min(int, int);
int max(int, int);
void setRenderDrawColor(TileColor color);
void drawTile(int x, int y);
void printGrid(Grid *grid);


#endif