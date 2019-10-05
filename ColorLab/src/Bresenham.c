#include <ColorLab/inc/Bresenham.h>
#include <math.h>

void Bresenham(Point begin, Point end, DrawLineFunc Func, void* args) {
    Point p = begin;
    int x0 = begin.x, x1 = end.x;
    int y0 = begin.y, y1 = end.y;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2 = 0;

    while (Func(p, args), x0 != x1 || y0 != y1) {
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
        p.x = x0; p.y = y0;
    }
}
