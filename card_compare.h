#ifndef CARD_COMPARE_H
#define CARD_COMPARE_H
#include "card.h"

//定义牌比较大小
namespace Card_Compare{
bool order_less(const Card& c1, const Card& c2);
}

namespace std {
template<>
struct less<Card>
{
    bool operator()(const Card& c1, const Card& c2) const
    {
        return Card_Compare::order_less(c1, c2);
    }
};
}
struct Value_Less
{
public:
    bool operator()(const Card& c1, const Card& c2) const
    {
        return c1.value() < c2.value();
    }
};

#endif // CARD_COMPARE_H
