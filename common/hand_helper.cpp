#include "hand_helper.h"

ValueMap Hand_Helper::count_value(const CardList &cards)
{
    ValueMap cmap;
    for (Card c : cards)
    {
        cmap[c].push_back(c);
    }
    return cmap;
}

// 返回可能的最大连续， 即 count为2可以代表1 count为3 可以代表2 count为4 可以代表3
// 返回最大连续 堆
// eg 3456789 ,1 -> 9, 4
// eg 3344667788, 2-> 8, 3
// eg 3334 ,3 -> 3, 1
// eg 333444 666, 3 -> 4, 2
// eg 333444 555666, 3 -> 6, 2
// eg 333444555777, 3 -> 6, 3
// eg 3334445555, 3 -> 4, 3
// eg 3334445555, 4 -> 5, 1
// eg 33335555, 4-> 5, 1
// with bool true
// eg 3455677 , 1, true -> 7, 5
// eg 33444555566, 2, true -> 6, 4
// eg 33444555566, 3, true -> 5, 2
std::pair<int, Card> Hand_Helper::find_max_group_by_count(const ValueMap &cmap, size_t count, bool can_over_flow)
{
    std::map<int, Card> c_map;

    Card val(Card::C_none, Card::V_none);
    int c_size = 0;

    static_assert(Card::V_none+1==Card::V_3, "");
    static_assert(Card::V_ace+1!=Card::V_2, "");

    c_map[c_size] = val;

    for (const ValuePair& p : cmap)
    {
        if (p.second.size() == count || (can_over_flow && p.second.size() > count))
        {
            //3334455566677788 == 3567
            if (Card::is_next(val.value(), p.first.value())) // none+1 = v_3
            {
                val = p.first;
                ++c_size;
            }
            else // v_3 +1 != v_5
            {
                c_map[c_size] = val; // push 1, v_3
                val = p.first; //val = 5
                c_size = 1;
            }
        }
    }
    c_map[c_size] = val;
//    qDebug() << *c_map.crbegin();
    return *c_map.crbegin();
}

int Hand_Helper::find_count_size(const ValueMap &cmap, size_t count, bool can_over_flow)
{
    int size = 0;
    for (const ValuePair& p : cmap)
    {
        if (p.second.size() == count || (can_over_flow && p.second.size() > count))
            ++size;
    }
    return size;
}

CardListList Hand_Helper::find_all_bomb(const ValueMap &cmap, Card::Value floor)
{
    CardListList lst;
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > floor && p.second.size() == 4)
        {
            lst.push_back(p.second);
        }
    }

    Card bjoker(Card::black_joker, Card::V_joker);
    ValueMap::const_iterator it = cmap.find(bjoker);
    if (it!=cmap.cend() && it->second.size() == 2)
    {
        lst.push_back(it->second);
    }
    return lst;
}


