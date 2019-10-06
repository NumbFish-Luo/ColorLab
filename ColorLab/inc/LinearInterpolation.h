#ifndef _COLOR_LAB_LINEAR_INTERPOLATION
#define _COLOR_LAB_LINEAR_INTERPOLATION

#include <ColorLab/inc/Color.h>
#include <ColorLab/inc/Base.h>

float LinearInterpolation(float begin, float end, float percent);
void LinearInterpolation_HSVA(const Color* begin, const Color* end, float percent, char reverseH, Color* result);
Point LinearInterpolation_Point(Point begin, Point end, float percent);

#endif // _COLOR_LAB_LINEAR_INTERPOLATION
