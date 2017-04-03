#include "card_compare.h"

// 先按面值大小比较，相同情况按颜色区分
bool order_less(const Card &c1, const Card &c2)
{
    return value_less(c1, c2)
            || (value_equal(c1, c2) && color_less(c1, c2));
}
