#include "hand_helper.h"


Hand_Helper::CountMap Hand_Helper::count_value(const std::set<Card> &cards)
{
    CountMap cmap;
    for (auto c : cards)
    {
        cmap[c]++;
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
std::pair<int, Card> Hand_Helper::find_max_group_by_count(const Hand_Helper::CountMap &cmap, int count, bool can_over_flow)
{
    std::map<int, Card> c_map;

    Card val(Card::C_none, Card::V_none);
    int c_size = 0;

    c_map[c_size] = val;

    for (auto p : cmap)
    {
        if (p.second == count || (can_over_flow && p.second > count))
        {
            //3334455566677788 == 3567
            if (val.value()+1 == p.first.value()) // none+1 = v_3
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

int Hand_Helper::find_count_size(const Hand_Helper::CountMap &cmap, int count, bool can_over_flow)
{
    int size = 0;
    for (auto p : cmap)
    {
        if (p.second == count || (can_over_flow && p.second > count))
            ++size;
    }
    return size;
}
