#include <ColorLab/inc/LinearInterpolation.h>

float LinearInterpolation(float begin, float end, float percent) { return begin + (end - begin) * (percent / 100); }

void LinearInterpolation_HSVA(const Color* begin, const Color* end, float percent, char reverseH, Color* result) {
    float beginH = begin->ops->GetH(begin);
    float endH = end->ops->GetH(end);
    if (reverseH > 0) { beginH += 360; } else if (reverseH < 0) { beginH -= 360; }
    result->ops->SetHSVA(result,
        LinearInterpolation(beginH, endH, percent),
        LinearInterpolation(begin->ops->GetS(begin), end->ops->GetS(end), percent),
        LinearInterpolation(begin->ops->GetV(begin), end->ops->GetV(end), percent),
        LinearInterpolation(begin->ops->GetA(begin), end->ops->GetA(end), percent)
    );
}

Point LinearInterpolation_Point(Point begin, Point end, float percent) {
    Point p;
    p.x = (SizeType)LinearInterpolation(begin.x, end.x, percent);
    p.y = (SizeType)LinearInterpolation(begin.y, end.y, percent);
    return p;
}
