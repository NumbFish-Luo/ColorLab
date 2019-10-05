#ifndef _COLOR_LAB_DRAW_LINE_H
#define _COLOR_LAB_DRAW_LINE_H

#include <ColorLab/inc/LinearInterpolation.h>
#include <ColorLab/inc/Bresenham.h>
#include <ColorLab/inc/Canvas.h>

// C = Canvas
#define _DrawLine(C, ...) DrawLine$_##C##_$##__VA_ARGS__
#define DrawLine(C, ...) _DrawLine(C, __VA_ARGS__)

// DEF
#define _DrawLine_DEF(C)                                                        \
/* typedef */                                                                   \
typedef struct {                                                                \
    C* canvas;                                                                  \
    Point p0, p1;                                                               \
    const Color* c0;                                                            \
    const Color* c1;                                                            \
    Bool reverseH;                                                              \
} DrawLine(C, _Args);                                                           \
/* func */                                                                      \
void DrawLine(C, _Do) (Point p, DrawLine(C, _Args)* args);                      \
void DrawLine(C) (C* canvas, Point p0, Point p1, const Color* c0, const Color* c1, Bool reverseH);
#define DrawLine_DEF(C) _DrawLine_DEF(C)

// IMPL
#define _DrawLine_IMPL(C)                                                       \
void DrawLine(C, _Do) (Point p, DrawLine(C, _Args)* args) {                     \
    float percent = Distance(p, args->p0) / Distance(args->p1, args->p0) * 100; \
    Color c;                                                                    \
    Color_Init(&c);                                                             \
    LinearInterpolation_HSVA(args->c0, args->c1, percent, args->reverseH, &c);  \
    args->canvas->ops->Set(args->canvas, p, &c);                                \
}                                                                               \
void DrawLine(C) (C* canvas, Point p0, Point p1, const Color* c0, const Color* c1, Bool reverseH) { \
    DrawLine(C, _Args) args;                                                    \
    args.canvas = canvas;                                                       \
    args.p0 = p0; args.p1 = p1;                                                 \
    args.c0 = c0; args.c1 = c1;                                                 \
    args.reverseH = reverseH;                                                   \
    Bresenham(p0, p1, DrawLine(C, _Do), &args);                                 \
}
#define DrawLine_IMPL(C) _DrawLine_IMPL(C)

#endif // _COLOR_LAB_DRAW_LINE_H
