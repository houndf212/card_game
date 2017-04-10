#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

void Hinter_Helper::push_back_n(CardList &target, const CardList &lst, size_t size)
{
    Q_ASSERT(lst.size() >= size);
    CardList::const_iterator it = lst.cbegin();
    while(size-- > 0)
    {
        target.push_back(*it++);
    }
}

void Hinter_Helper::push_back(CardList &target, const CardList &lst)
{
    push_back_n(target, lst, lst.size());
}

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
    Q_ASSERT(std::is_sorted(target.cbegin(), target.cend()));
    Q_ASSERT(std::is_sorted(m.cbegin(), m.cend()));
    CardList::const_iterator start = std::find_first_of(target.cbegin(), target.cend(),
                                                        m.cbegin(), m.cend());
    Q_ASSERT(start != m.cend());
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
        push_back(ret, ll);
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
            push_back_n(l, p.second, 2);
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
        remove_map(m, CardList(1, c1));
        CardList list2 = find_B_by_cmap(m, Card::V_none);
        for (const Card& c2 : list2)
        {
            CardList bc;
            std::pair<Card, Card> p = std::minmax(c1, c2);
            bc.push_back(p.first);
            bc.push_back(p.second);
            ret.push_back(bc);
        }
    }

    // remove duplicate
    ret.resize(std::distance(ret.begin(), std::unique(ret.begin(), ret.end())));
    return ret;
}

CardListList Hinter_Helper::find_AAAA_by_cmap(const ValueMap &cmap, Card::Value floor)
{
    CardListList lst;
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > floor
                && p.second.size() == 4)
        {
            lst.push_back(p.second);
        }
    }
    return lst;
}

CardListList Hinter_Helper::find_BBCC_by_cmap(const ValueMap &cmap)
{
    CardListList ret;
    CardListList list_bb = find_BB_by_cmap(cmap, Card::V_none);
    for (const CardList& bb : list_bb)
    {
        ValueMap m = cmap;
        remove_map(m, bb);
        CardListList list_cc = find_BB_by_cmap(m, Card::V_none);
        for (const CardList& cc : list_cc)
        {
            CardList bbcc = bb;
            push_back(bbcc, cc);
            sort(bbcc);
            ret.push_back(bbcc);
        }
    }
    // remove duplicate
    ret.resize(std::distance(ret.begin(), std::unique(ret.begin(), ret.end())));
    return ret;
}

ValueMap Hinter_Helper::get_map_greater_value_size(const ValueMap &cmap, Card::Value val, size_t size)
{
    ValueMap m;
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > val && p.second.size() >= size)
            m.insert(p);
    }
    return m;
}

CardListList Hinter_Helper::slice_to_group(const ValueMap &cmap, Card::Value val, size_t size)
{
    CardListList ret;
    ValueMap m = get_map_greater_value_size(cmap, val, size);
    if (m.empty())
        return ret;

    ValueMap::const_iterator it = m.cbegin();
    const ValuePair& p_start = *it;
    Card card = p_start.first;
    CardList current_list;
    push_back_n(current_list, p_start.second, size);

    for (++it; it!=m.cend(); ++it)
    {
        const ValuePair& p = *it;
        if (Card::is_next(card.value(), p.first.value()))
        {
            card = p.first;
            push_back_n(current_list, p.second, size);
        }
        else
        {
            ret.push_back(current_list);
            card = p.first;
            current_list.clear();
            push_back_n(current_list, p.second, size);
        }
    }
    if (!current_list.empty())
        ret.push_back(current_list);

    return ret;
}

CardListList Hinter_Helper::find_AAA_by_cmap(const ValueMap &cmap, Card::Value floor)
{
    CardListList lst[2]; // 0-3,1-4
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > floor
                && p.second.size()>=3)
        {
            CardList l;
            push_back_n(l, p.second, 3);
            lst[p.second.size()-3].push_back(l);
        }
    }

    CardListList ret = lst[0];

    for (const CardList& l : lst[1])
    {
        ret.push_back(l);
    }
    return ret;
}

CardListList Hinter_Helper::find_N_by_cmap(const ValueMap &cmap, int n)
{

}
