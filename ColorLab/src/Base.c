#include <ColorLab/inc/Base.h>
#include <math.h>

float Distance(Point p0, Point p1) { return sqrtf(powf((float)p1.x - p0.x, 2) + powf((float)p1.y - p0.y, 2)); }
