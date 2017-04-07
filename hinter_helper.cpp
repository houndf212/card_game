#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

CardList Hinter_Helper::remove_list(const CardList &source, const CardList &m)
{
    Q_ASSERT(std::is_sorted(source.cbegin(), source.cend(), std::less<Card>()));
    Q_ASSERT(std::is_sorted(m.cbegin(), m.cend(), std::less<Card>()));
    CardList target = source;
    CardList::const_iterator start = std::find_first_of(target.cbegin(), target.cend(),
                                                        m.cbegin(), m.cend(),
                                                        std::less<Card>());
    target.erase(start + m.size());
    return target;
}

////CardList Hinter_Helper::remove(const CardList &source, const Card& card)
////{
////    CardList ret;
////    std::remove_copy_if(source.cbegin(), source.cend(),
////                        std::back_inserter(ret),
////                        std::bind(std::equal_to<Card>(), std::placeholders::_1, card));
////    return ret;
////}

CardListList Hinter_Helper::find_B(const CardList &cards)
{
    ValueMap cmap = Hand_Helper::count_value(cards);
    return find_B_by_cmap(cmap, Card::V_none);
}

CardListList Hinter_Helper::find_B_by_cmap(const ValueMap &cmap, Card::Value floor)
{
    CardListList lst[4];
    for (const ValuePair& p : cmap)
    {
        Card c = p.first;
        if (c.value() > floor)
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

CardListList Hinter_Helper::find_BB_by_cmap(const ValueMap &cmap, Card::Value floor)
{
    CardListList lst[3]; // 0-2,1-3,2-4
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > floor
                && p.second.size()>=2)
        {
            CardList l;
            l.push_back(p.second.at(0));
            l.push_back(p.second.at(1));
            lst[p.second.size()-2].push_back(l);
        }
    }
    //take out double Joker to 4
    if (lst[0].back().front().value() == Card::V_joker)
    {
        lst[2].push_back(lst[0].back());
        lst[0].pop_back();
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

CardListList Hinter_Helper::find_BB(const CardList &cards)
{
    ValueMap cmap = Hand_Helper::count_value(cards);
    return find_BB_by_cmap(cmap, Card::V_none);
}

ValueMap Hinter_Helper::remove_map(const ValueMap &cmap, const CardList &lst)
{
    ValueMap m = cmap;
    ValueMap::iterator it = m.find(lst.front());
    Q_ASSERT(it!=m.end());
    CardList& target = it->second;

    Q_ASSERT(std::is_sorted(target.cbegin(), target.cend(), std::less<Card>()));
    Q_ASSERT(std::is_sorted(lst.cbegin(), lst.cend(), std::less<Card>()));

    CardList::const_iterator p = std::find_first_of(target.cbegin(), target.cend(),
                                                    lst.cbegin(), lst.cend(),
                                                    std::equal_to<Card>());
    Q_ASSERT(p!=target.cend());
    target.erase(p, p+lst.size());
    return m;
}
