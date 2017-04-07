#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

CardList Hinter_Helper::remove_in(const CardList &source, const Card& card)
{
    CardList ret;
    std::remove_copy_if(source.cbegin(), source.cend(),
                        std::back_inserter(ret),
                        std::bind(Value_Equal(), std::placeholders::_1, card));
    return ret;
}

CardListList Hinter_Helper::find_B(const CardList &cards)
{
    Hand_Helper::ValueMap cmap = Hand_Helper::count_value(cards);
    return find_B_by_map(cmap, Card::V_none);
}

CardListList Hinter_Helper::find_B_by_map(const Hand_Helper::ValueMap &cmap, Card::Value val)
{
    CardListList lst[4];
    for (const Hand_Helper::ValuePair& p : cmap)
    {
        Card c = p.first;
        if (c.value() > val)
        {
            CardList l;
            l.push_back(c);
            size_t size = p.second.size();
            Q_ASSERT(1<=size && size<=4);
            lst[size-1].push_back(l);
        }
    }

    CardListList ret;
    for (const CardListList& ll :lst)
    {
        for (const CardList& l : ll)
        {
            ret.push_back(l);
        }
    }
    return ret;
}
