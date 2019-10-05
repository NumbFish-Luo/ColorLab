#include <ColorLab/inc/Color.h>
#include <ColorLab/inc/Base.h>
#include <math.h>

#define RGBA  this->_rgba
#define HSVA  this->_hsva
#define R     RGBA[0]
#define G     RGBA[1]
#define B     RGBA[2]
#define A_RGB RGBA[3]
#define H     HSVA[0]
#define S     HSVA[1]
#define V     HSVA[2]
#define A_HSV HSVA[3]

static inline void FixInRange(float* f, float min, float max) {
    if (*f < min) { *f = min; } else if (*f > max) { *f = max; }
}

static void SetRGBA(Color* this, float r, float g, float b, float a) {
    float delta, max, min;
    FixInRange(&r, 0, 255);
    FixInRange(&g, 0, 255);
    FixInRange(&b, 0, 255);
    FixInRange(&a, 0, 255);
    R = r; G = g; B = b; A_RGB = A_HSV = a;
    max = fmaxf(fmaxf(r, g), b);
    min = fminf(fminf(r, g), b);
    delta = max - min;
    if (delta == 0) { H = 0; }
    else if (max == r) { H = 60 * fmodf((g - b) / delta, 6); }
    else if (max == g) { H = 60 * ((b - r) / delta + 2); }
    else if (max == b) { H = 60 * ((r - g) / delta + 4); }
    S = (max == 0) ? 0 : (delta / max * 100);
    V = max / 2.55f;
}

static void SetHSVA(Color* this, float h, float s, float v, float a) {
    float c, x, m, r, g, b;
    h = fmodf(h, 360);
    FixInRange(&s, 0, 100);
    FixInRange(&v, 0, 100);
    FixInRange(&a, 0, 255);
    H = h; S = s; V = v; A_HSV = A_RGB = a;
    s /= 100; v /= 100;
    c = v * s;
    x = c * (1 - fabsf(fmodf(h / 60, 2) - 1));
    m = v - c;
    switch ((int)(h / 60)) {
    case 0: r = c; g = x; b = 0; break;
    case 1: r = x; g = c; b = 0; break;
    case 2: r = 0; g = c; b = x; break;
    case 3: r = 0; g = x; b = c; break;
    case 4: r = x; g = 0; b = c; break;
    case 5: r = c; g = 0; b = x; break;
    default: r = g = b = -m; break;
    }
    R = (r + m) * 255;
    G = (g + m) * 255;
    B = (b + m) * 255;
}

static float GetR (const Color* this) { return R; }
static float GetG (const Color* this) { return G; }
static float GetB (const Color* this) { return B; }
static float GetH (const Color* this) { return H; }
static float GetS (const Color* this) { return S; }
static float GetV (const Color* this) { return V; }
static float GetA (const Color* this) { return A_RGB; }
static const float* GetRGBA(const Color* this) { return RGBA; }
static const float* GetHSVA(const Color* this) { return HSVA; }

static Color_ops* ColorOps(void) {
    static Color_ops ops;
    static Bool init = False;
    if (init == False) {
        init = True;
        ops.SetRGBA = SetRGBA;
        ops.SetHSVA = SetHSVA;
        ops.GetR    = GetR;
        ops.GetG    = GetG;
        ops.GetB    = GetB;
        ops.GetH    = GetH;
        ops.GetS    = GetS;
        ops.GetV    = GetV;
        ops.GetA    = GetA;
        ops.GetRGBA = GetRGBA;
        ops.GetHSVA = GetHSVA;
    }
    return &ops;
}

void Color_Init(Color* this) { this->ops = ColorOps(); }

const Color* Color_White(void) { 
    static Color c;
    static Bool init = False;
    if (init == False) {
        init = True;
        Color_Init(&c);
        c.ops->SetRGBA(&c, 255, 255, 255, 255);
    }
    return &c;
}

const Color* Color_Black(void) { 
    static Color c;
    static Bool init = False;
    if (init == False) {
        init = True;
        Color_Init(&c);
        c.ops->SetRGBA(&c, 0, 0, 0, 255);
    }
    return &c;
}

#undef RGBA
#undef HSVA
#undef R
#undef G
#undef B
#undef A_RGB
#undef H
#undef S
#undef V
#undef A_HSV
