#ifndef _COLOR_LAB_TYPE_H
#define _COLOR_LAB_TYPE_H

typedef unsigned char  Byte;
typedef unsigned short Word;
typedef unsigned int   SizeType;
typedef enum { False = 0, True = 1 } Bool;
typedef struct { SizeType x, y; } Point;
float Distance(Point p0, Point p1);

#endif // _COLOR_LAB_TYPE_H
