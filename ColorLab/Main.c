#include <stdio.h>
#include <ColorLab/inc/DrawLine.h>

// 无视vs的两个很烦的警告
#pragma warning(disable: 4996)
#pragma warning(disable: 6262)

#define W 8 // 宽
#define H 8 // 高
#define D 3 // 深度, 3 = RGB, 4 = RGBA

Canvas_DEF(W, H, D);  DrawLine_DEF(Canvas(W, H, D));  // 定义模板
Canvas_IMPL(W, H, D); DrawLine_IMPL(Canvas(W, H, D)); // 实现模板

int main(void) {
    // 定义画布, 起点坐标p0, 终点坐标p1; 起点颜色c0, 终点颜色c1
    Canvas(W, H, D) canvas;
    Point p0, p1;
    Color c0, c1;

    // 初始化画布和颜色
    Canvas(W, H, D, _Init) (&canvas);
    Color_Init(&c0);
    Color_Init(&c1);

    // 设置起点颜色和终点颜色, 此处用HSV颜色空间模型表示
    c0.ops->SetHSVA(&c0, 180, 50,  75, 255);
    c1.ops->SetHSVA(&c1,   0, 25, 100, 255);

    // 设置坐标画线
    // 最后一个参数大于0时第一个颜色色相+360, 小于0时第一个颜色色相-360, 等于0时不进行色相修改操作
    p0.x = 0; p0.y = 0;
    p1.x = 0; p1.y = 7;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c0, &c1, 0);

    p0.x = 0; p0.y = 7;
    p1.x = 7; p1.y = 7;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c1, &c0, 1);

    p0.x = 7; p0.y = 7;
    p1.x = 7; p1.y = 0;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c0, &c1, 0);

    p0.x = 7; p0.y = 0;
    p1.x = 0; p1.y = 0;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c1, &c0, 1);

    canvas.ops->Save(&canvas, "test.png"); // 保存画布
    return 0;
}
