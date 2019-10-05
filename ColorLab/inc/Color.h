#ifndef _COLOR_LAB_COLOR_H
#define _COLOR_LAB_COLOR_H

typedef struct Color Color;
typedef struct Color_ops Color_ops;

struct Color {
    float _rgba[4];
    float _hsva[4];
    Color_ops* ops;
};

struct Color_ops {
    void (*SetRGBA) (Color* this, float r, float g, float b, float a);
    void (*SetHSVA) (Color* this, float h, float s, float v, float a);
    float (*GetR) (const Color* this);
    float (*GetG) (const Color* this);
    float (*GetB) (const Color* this);
    float (*GetH) (const Color* this);
    float (*GetS) (const Color* this);
    float (*GetV) (const Color* this);
    float (*GetA) (const Color* this);
    const float* (*GetRGBA) (const Color* this);
    const float* (*GetHSVA) (const Color* this);
};

void Color_Init(Color* this);
const Color* Color_White(void);
const Color* Color_Black(void);

#endif // _COLOR_LAB_COLOR_H
