#include "card_compare.h"

// 先按面值大小比较，相同情况按颜色区分
bool Card_Compare::order_less(const Card &c1, const Card &c2)
{
    return c1.value() < c2.value()
            || (c1.value() == c2.value() && c1.color() < c2.color());
}

bool Card_Compare::order_equal(const Card &c1, const Card &c2)
{
    return c1.color()==c2.color() && c1.value()==c2.value();
}
