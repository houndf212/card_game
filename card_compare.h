#ifndef CARD_COMPARE_H
#define CARD_COMPARE_H

#include <set>
#include <vector>
#include <list>
#include <map>
#include "card.h"

//定义牌比较大小
namespace Card_Compare{
bool order_less(const Card& c1, const Card& c2);
bool order_equal(const Card& c1, const Card& c2);
}

inline bool operator<(const Card& c1, const Card& c2)
{
    return Card_Compare::order_less(c1, c2);
}
inline bool operator==(const Card& c1, const Card& c2)
{
    return Card_Compare::order_equal(c1, c2);
}

//namespace std {
//template<>
//struct less<Card>
//{
//    bool operator()(const Card& c1, const Card& c2) const
//    {
//        return Card_Compare::order_less(c1, c2);
//    }
//};

//template<>
//struct equal_to<Card>
//{
//    bool operator()(const Card& c1, const Card& c2) const
//    {
//        return Card_Compare::order_equal(c1, c2);
//    }
//};
//}

struct Value_Less
{
public:
    bool operator()(const Card& c1, const Card& c2) const
    {
        return c1.value() < c2.value();
    }
};

struct Value_Equal
{
public:
    bool operator()(const Card& c1, const Card& c2) const
    {
        return c1.value() == c2.value();
    }
};

typedef std::set<Card> CardSet;
typedef std::vector<Card> CardList;
typedef std::vector<CardList> CardListList;
//typedef std::list<Card> CardList;
//typedef std::list<CardList> CardListList;

typedef std::map<Card, CardList, Value_Less> ValueMap;
typedef ValueMap::value_type ValuePair;

#endif // CARD_COMPARE_H
