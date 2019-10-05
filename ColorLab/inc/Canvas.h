#ifndef _COLOR_LAB_CANVAS_H
#define _COLOR_LAB_CANVAS_H

#include <ColorLab/inc/Base.h>
#include <ColorLab/inc/Color.h>
#include <ColorLab/inc/svpng.inc>

// Width, Height, Depth, ...
#define _Canvas(W, H, D, ...) Canvas$_##W##x##H##x##D##_$##__VA_ARGS__
#define Canvas(W, H, D, ...) _Canvas(W, H, D, __VA_ARGS__)

// DEF
#define _Canvas_DEF(W, H, D)                                                    \
/* typedef */                                                                   \
typedef struct Canvas(W, H, D) Canvas(W, H, D);                                 \
typedef struct Canvas(W, H, D, _ops) Canvas(W, H, D, _ops);                     \
/* struct */                                                                    \
struct Canvas(W, H, D) {                                                        \
    Byte _data[W * H * D];                                                      \
    Canvas(W, H, D, _ops)* ops;                                                 \
};                                                                              \
struct Canvas(W, H, D, _ops) {                                                  \
    Bool (*Set ) (Canvas(W, H, D)* this, Point p, const Color* c);              \
    Bool (*Get ) (const Canvas(W, H, D)* this, Point p, Color* c);              \
    void (*Save) (const Canvas(W, H, D)* this, const char* fileName);           \
};                                                                              \
/* init */                                                                      \
void Canvas(W, H, D, _Init) (Canvas(W, H, D)* this);
#define Canvas_DEF(W, H, D) _Canvas_DEF(W, H, D)

// IMPL
#define _Canvas_IMPL(W, H, D)                                                   \
/* static */                                                                    \
static Bool Canvas(W, H, D, _GetPoint) (const Canvas(W, H, D)* this, Point p, const Byte** b) { \
    if (p.x < 0 || p.x >= W || p.y < 0 || p.y >= H) { return False; }           \
    *b = this->_data + (p.y * W + p.x) * D;                                     \
    return True;                                                                \
}                                                                               \
static Bool Canvas(W, H, D, _Set) (Canvas(W, H, D)* this, Point p, const Color* c) { \
    Byte i;                                                                     \
    Byte* b;                                                                    \
    if (Canvas(W, H, D, _GetPoint) (this, p, &b) == False) { return False; }    \
    for (i = 0; i < D; ++i) { *b++ = (Byte)c->ops->GetRGBA(c)[i]; }             \
    return True;                                                                \
}                                                                               \
static Bool Canvas(W, H, D, _Get) (const Canvas(W, H, D)* this, Point p, Color* c) { \
    Byte i;                                                                     \
    Byte* b;                                                                    \
    float rgba[4] = { 255, 255, 255, 255 };                                     \
    if (Canvas(W, H, D, _GetPoint) (this, p, &b) == False) { return False; }    \
    for (i = 0; i < D; ++i) { rgba[i] = (float)*b++; }                          \
    c->ops->SetRGBA(c, rgba[0], rgba[1], rgba[2], rgba[3]);                     \
    return True;                                                                \
}                                                                               \
static void Canvas(W, H, D, _Save) (const Canvas(W, H, D)* this, const char* fileName) { \
    FILE* fp = fopen(fileName, "wb");                                           \
    svpng(fp, W, H, this->_data, D == 4);                                       \
    fclose(fp);                                                                 \
}                                                                               \
static Canvas(W, H, D, _ops)* Canvas(W, H, D, Ops) (void) {                     \
    static Canvas(W, H, D, _ops) ops;                                           \
    static Bool init = False;                                                   \
    if (init == False) {                                                        \
        init = True;                                                            \
        ops.Set  = Canvas(W, H, D, _Set );                                      \
        ops.Get  = Canvas(W, H, D, _Get );                                      \
        ops.Save = Canvas(W, H, D, _Save);                                      \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* init */                                                                      \
void Canvas(W, H, D, _Init) (Canvas(W, H, D)* this) {                           \
    this->ops = Canvas(W, H, D, Ops) ();                                        \
}
#define Canvas_IMPL(W, H, D) _Canvas_IMPL(W, H, D)

#endif // _COLOR_LAB_CANVAS_H
