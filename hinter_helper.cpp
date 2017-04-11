#include "hinter_helper.h"
#include <algorithm>
#include <functional>
#include "hand_helper.h"

// lst {333444} prime_size = 3 type_size = 2
void Hinter_Helper::remove_map_same_value(ValueMap &cmap, const CardList &lst, size_t prime_size, size_t type_size)
{
    Q_ASSERT(prime_size>0);
    Q_ASSERT(prime_size*type_size==lst.size());
    for (CardList::const_iterator beg = lst.cbegin();
         beg!=lst.cend();)
    {
        CardList same_value_list;
        int k = prime_size;
        while(k-- > 0)
        {
            same_value_list.push_back(*beg++);
        }
        ValueMap::iterator it = cmap.find(same_value_list.front());
        Q_ASSERT(it!=cmap.end());
        CardList& target = it->second;
        remove_list_same_value(target, same_value_list);
        if (target.empty())
            cmap.erase(it);
    }
}

void Hinter_Helper::remove_list_same_value(CardList &target, const CardList &m)
{
    Q_ASSERT(std::is_sorted(target.cbegin(), target.cend()));
    Q_ASSERT(std::is_sorted(m.cbegin(), m.cend()));
    Q_ASSERT(m.front().value() == m.back().value());
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
    if (lst[0].size()>0 && lst[0].back().front().value() == Card::V_joker)
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
        remove_map_same_value(m, CardList(1, c1), 1, 1);
        CardList list2 = find_B_by_cmap(m, Card::V_none);
        for (const Card& c2 : list2)
        {
            CardList s;
            s.push_back(c1);
            s.push_back(c2);
            sort(s);
            ret.push_back(s);
        }
    }

    // remove duplicate
    ret.resize(std::distance(ret.begin(), std::unique(ret.begin(), ret.end())));
    return ret;
}
CardListList Hinter_Helper::find_N_by_cmap(const ValueMap &cmap, int n)
{
    CardListList ret;
    find_N_recursion(ret, cmap, CardList(), n);
    for (CardList& l : ret)
    {
        sort(l);
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
        remove_map_same_value(m, bb, 2, 1);
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

ValueMap Hinter_Helper::get_map_greater_value_size(const ValueMap &cmap, Card::Value val, size_t prime_size)
{
    ValueMap m;
    for (const ValuePair& p : cmap)
    {
        if (p.first.value() > val && p.second.size() >= prime_size)
            m.insert(p);
    }
    return m;
}

CardListList Hinter_Helper::slice_to_group(const ValueMap &cmap, Card::Value val, size_t type_size, size_t prime_size)
{
    CardListList groups;
    ValueMap m = get_map_greater_value_size(cmap, val, prime_size);
    if (m.empty())
        return groups;

    ValueMap::const_iterator it = m.cbegin();
    const ValuePair& p_start = *it;
    Card card = p_start.first;
    CardList current_list;
    push_back_n(current_list, p_start.second, prime_size);

    for (++it; it!=m.cend(); ++it)
    {
        const ValuePair& p = *it;
        if (Card::is_next(card.value(), p.first.value()))
        {
            card = p.first;
            push_back_n(current_list, p.second, prime_size);
        }
        else
        {
            groups.push_back(current_list);
            card = p.first;
            current_list.clear();
            push_back_n(current_list, p.second, prime_size);
        }
    }
    if (!current_list.empty())
        groups.push_back(current_list);

    groups = find_group(groups, type_size, prime_size);
    //move bomb value to end
    CardListList normal_list, bomb_list;
    for (const CardList& lst : groups)
    {
        if (is_bomb_list(cmap, lst))
            bomb_list.push_back(lst);
        else
            normal_list.push_back(lst);
    }
    for (const CardList& l : bomb_list)
    {
        normal_list.push_back(l);
    }
    return normal_list;
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

void Hinter_Helper::find_N_recursion(CardListList &all, const ValueMap &cmap, const CardList &lst, int n)
{
    CardList lb = Hinter_Helper::find_B_by_cmap(cmap, Card::V_none);
    for (const Card& c : lb)
    {
        if (n == 1)
        {
            CardList l = lst;
            l.push_back(c);
            all.push_back(l);
        }
        else
        {
            CardList l = lst;
            l.push_back(c);
            ValueMap m = cmap;
            remove_map_same_value(m, CardList(1, c), 1, 1);
            find_N_recursion(all, m, l, n-1);
        }
    }
}

CardListList Hinter_Helper::get_left_N(const ValueMap &cmap, size_t n)
{
    CardListList ret;
    CardList lst = get_list_by_count(cmap);

    Q_ASSERT(lst.size() >= n);
    CardList::const_iterator beg = lst.cbegin();
    CardList::const_iterator end = beg;
    std::advance(end, n);
    for ( ;end!=lst.cend(); ++beg, ++end)
    {
        ret.push_back(CardList(beg, end));
    }
    ret.push_back(CardList(beg, end));
    return ret;
}

CardList Hinter_Helper::get_list_by_count(const ValueMap &cmap)
{
    CardList lst[4]; // 0-1, 1-2, 2-3, 3-4
    for (const ValuePair& p : cmap)
    {
        size_t size = p.second.size();
        Q_ASSERT(1<=size && size<=4);
        push_back(lst[size-1], p.second);
    }

    // remove double joker to 4
    CardList& l2 = lst[1];
    if (l2.size() >= 2)
    {
        CardList::const_reverse_iterator rbeg = l2.crbegin();
        if (rbeg->color() == Card::red_joker)
        {
            ++rbeg;
            if (rbeg->color() == Card::black_joker)
            {
                Card r = l2.back();
                l2.pop_back();
                Card b = l2.back();
                l2.pop_back();
                lst[3].push_back(b);
                lst[3].push_back(r);
            }
        }
    }

    CardList all_list;
    for (const CardList& ll :lst)
    {
        push_back(all_list, ll);
    }
    return all_list;
}

bool Hinter_Helper::is_bomb_list(const ValueMap &cmap, const CardList &lst)
{
    for (const Card& c : lst)
    {
        ValueMap::const_iterator p = cmap.find(c);
        Q_ASSERT(p!=cmap.cend());
        if (p->second.size() == 4)
            return true;
    }
    return false;
}

CardListList Hinter_Helper::find_group(const CardListList &groups, size_t type_size, size_t prime_size)
{
    CardListList ret;
    for (const CardList& lst : groups)
    {
        if (lst.size() < type_size*prime_size) continue;

        CardList::const_iterator beg = lst.cbegin();
        CardList::const_iterator end = beg;
        std::advance(end, type_size*prime_size);
        for (; end!=lst.cend();
             std::advance(beg, prime_size), std::advance(end, prime_size))
        {
            ret.push_back(CardList(beg, end));
        }
        ret.push_back(CardList(beg, end));
    }
    return ret;
}
