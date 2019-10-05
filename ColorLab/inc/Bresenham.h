#ifndef _COLOR_LAB_BRESENHAM_H
#define _COLOR_LAB_BRESENHAM_H

#include <ColorLab/inc/Base.h>

typedef void (*DrawLineFunc) (Point p, void* args);

void Bresenham(Point begin, Point end, DrawLineFunc Func, void* args);

#endif // _COLOR_LAB_BRESENHAM_H
