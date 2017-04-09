#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

void Hinter_Helper::remove_map(ValueMap &cmap, const CardList &lst)
{
    Q_ASSERT(lst.front().value() == lst.back().value());
    ValueMap::iterator it = cmap.find(lst.front());
    Q_ASSERT(it!=cmap.end());
    CardList& target = it->second;
    remove_list(target, lst);
    if (target.empty())
        cmap.erase(it);
}

void Hinter_Helper::remove_list(CardList &target, const CardList &m)
{
    Q_ASSERT(std::is_sorted(target.cbegin(), target.cend(), std::less<Card>()));
    Q_ASSERT(std::is_sorted(m.cbegin(), m.cend(), std::less<Card>()));
    CardList::const_iterator start = std::find_first_of(target.cbegin(), target.cend(),
                                                        m.cbegin(), m.cend(),
                                                        std::less<Card>());
    CardList::const_iterator end = start;
    std::advance(end, m.size());
    target.erase(start, end);
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
            CardList::const_iterator it = p.second.cbegin();
            l.push_back(*it++);
            l.push_back(*it);
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

CardListList Hinter_Helper::find_BC_by_cmap(const ValueMap &cmap)
{
    CardListList ret;
    CardList list1 = find_B_by_cmap(cmap, Card::V_none);
    for (const Card& c1 : list1)
    {
        ValueMap m = cmap;
        CardList l;
        l.push_back(c1);
        remove_map(m, l);
        CardList list2 = find_B_by_cmap(m, Card::V_none);
        for (const Card& c2 : list2)
        {
            CardList bc;
            std::pair<Card, Card> p = std::minmax(c1, c2, std::less<Card>());
            bc.push_back(p.first);
            bc.push_back(p.second);
            ret.push_back(bc);
        }
    }

    // remove duplicate
    ret.resize(std::distance(ret.begin(), std::unique(ret.begin(), ret.end(), &is_same_BC)));
    return ret;
}

bool Hinter_Helper::is_same_BC(const CardList &l1, const CardList &l2)
{
    Q_ASSERT(l1.size() == 2);
    Q_ASSERT(l2.size() == 2);
    std::less<Card> cmp;
    return cmp(l1.front(), l2.front()) && cmp(l1.back(), l2.back());
}
