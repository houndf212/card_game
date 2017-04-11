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

void push_back_n(CardList &target, const CardList &lst, size_t size)
{
    Q_ASSERT(lst.size() >= size);
    CardList::const_iterator it = lst.cbegin();
    while(size-- > 0)
    {
        target.push_back(*it++);
    }
}

void push_back(CardList &target, const CardList &lst)
{
    push_back_n(target, lst, lst.size());
}
