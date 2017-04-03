#ifndef CARD_COMPARE_H
#define CARD_COMPARE_H
#include "card.h"

//定义牌比较大小

typedef bool (*Card_Compare)(const Card& , const Card& );

inline bool color_less(const Card& c1, const Card& c2)
{
    return c1.color() < c2.color();
}

inline bool color_equal(const Card& c1, const Card& c2)
{
    return c1.color() == c2.color();
}

inline bool value_less(const Card& c1, const Card& c2)
{
    return c1.value() < c2.value();
}

inline bool value_equal(const Card& c1, const Card& c2)
{
    return c1.value() == c2.value();
}

inline bool order_equal(const Card& c1, const Card& c2)
{
    return color_equal(c1, c2) && value_equal(c1, c2);
}

bool order_less(const Card& c1, const Card& c2);

inline bool operator<(const Card& c1, const Card& c2)
{
    return order_less(c1, c2);
}

//namespace std
//{
//template<>
//struct less<Card>
//{
//    bool operator ()(const Card& c1, const Card& c2)
//    {
//        return order_less(c1, c2);
//    }
//};
//}
#endif // CARD_COMPARE_H
