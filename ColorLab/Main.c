#include <stdio.h>
#include <ColorLab/inc/DrawLine.h>

// ����vs�������ܷ��ľ���
#pragma warning(disable: 4996)
#pragma warning(disable: 6262)

#define W 8 // ��
#define H 8 // ��
#define D 3 // ���, 3 = RGB, 4 = RGBA

Canvas_DEF(W, H, D);  DrawLine_DEF(Canvas(W, H, D));  // ����ģ��
Canvas_IMPL(W, H, D); DrawLine_IMPL(Canvas(W, H, D)); // ʵ��ģ��

int main(void) {
    // ���廭��, �������p0, �յ�����p1; �����ɫc0, �յ���ɫc1
    Canvas(W, H, D) canvas;
    Point p0, p1;
    Color c0, c1;

    // ��ʼ����������ɫ
    Canvas(W, H, D, _Init) (&canvas);
    Color_Init(&c0);
    Color_Init(&c1);

    // ���������ɫ���յ���ɫ, �˴���HSV��ɫ�ռ�ģ�ͱ�ʾ
    c0.ops->SetHSVA(&c0, 180, 50,  75, 255);
    c1.ops->SetHSVA(&c1,   0, 25, 100, 255);

    // �������껭��, False��ʾ������ɫ�෴ת��ֵ, True��ʾ����ɫ�෴ת��ֵ
    p0.x = 0; p0.y = 0;
    p1.x = 0; p1.y = 7;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c0, &c1, False);

    p0.x = 0; p0.y = 7;
    p1.x = 7; p1.y = 7;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c1, &c0, True);

    p0.x = 7; p0.y = 7;
    p1.x = 7; p1.y = 0;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c0, &c1, False);

    p0.x = 7; p0.y = 0;
    p1.x = 0; p1.y = 0;
    DrawLine(Canvas(W, H, D)) (&canvas, p0, p1, &c1, &c0, True);

    canvas.ops->Save(&canvas, "test.png"); // ���滭��
    return 0;
}
