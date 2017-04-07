#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

void Hinter_Helper::remove_map(ValueMap &cmap, const CardList &lst)
{
    ValueMap::iterator it = cmap.find(lst.front());
    Q_ASSERT(it!=cmap.end());
    CardList& target = it->second;
    remove_list(target, lst);
}

void Hinter_Helper::remove_list(CardList &target, const CardList &m)
{
    Q_ASSERT(std::is_sorted(target.cbegin(), target.cend(), std::less<Card>()));
    Q_ASSERT(std::is_sorted(m.cbegin(), m.cend(), std::less<Card>()));
    CardList::const_iterator start = std::find_first_of(target.cbegin(), target.cend(),
                                                        m.cbegin(), m.cend(),
                                                        std::less<Card>());
    target.erase(start + m.size());
}


CardList Hinter_Helper::find_B_by_cmap(const ValueMap &cmap, Card::Value floor)
{
    CardList lst[4];
    for (const ValuePair& p : cmap)
    {
        Card c = p.first;
        if (c.value() > floor)
        {
            size_t size = p.second.size();
            Q_ASSERT(1<=size && size<=4);
            lst[size-1].push_back(c);
        }
    }

    CardList ret;
    for (const CardList& ll :lst)
    {
        for (const Card& l : ll)
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
