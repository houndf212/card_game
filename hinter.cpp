#include "hinter.h"
#include "hinter_helper.h"

CardList Hand_Hinter::next_hint()
{
    CardList lst = m_hint_queue.front();
    m_hint_queue.pop();
    m_hint_queue.push(lst);
    return lst;
}

void Hand_Hinter::set_hand(const CardList &cards, const CardList &pre_hand)
{
    m_cards = cards;
    m_cmap = Hand_Helper::count_value(m_cards);

    Hand_Info info;
    info.set_cards(pre_hand);
    Q_ASSERT(info.isValid());

    m_pre_hand = info;
    m_hint_queue = std::queue<CardList>(); //clear

    if (m_cards.size() >= m_pre_hand.size())
    {
        switch (info.type())
        {
        case Hand_Info::Null:
            process_type_Null();
            break;
        case Hand_Info::A:
            if (info.type_size() == 1)
            {
                process_type_A();
            }
            else
            {
                Q_ASSERT(info.type_size()>=5);
                process_type_A_plus();
            }
            break;
        case Hand_Info::AA:
            if (info.type_size() == 1)
            {
                process_type_AA();
            }
            else
            {
                process_type_AA_plus();
            }
            break;
        case Hand_Info::AAA:
            if (info.type_size() == 1)
            {
                process_type_AAA();
            }
            else
            {
                process_type_A_AA_AAA_plus();
            }
            break;
        case Hand_Info::AAAB:
            process_type_AAAB();
            break;
        case Hand_Info::AAABB:
            process_type_AAABB();
            break;
        case Hand_Info::AAAABC:
            process_type_AAAABC();
            break;
        case Hand_Info::AAAABBCC:
            process_type_AAAABBCC();
            break;
        case Hand_Info::Bomb:
            break;
        default:
            Q_ASSERT(false);
            break;
        }
    }
    add_bomb_to_end();
}

void Hand_Hinter::process_type_Null()
{

}

void Hand_Hinter::process_type_A()
{
    CardList lst = Hinter_Helper::find_B_by_cmap(m_cmap, m_pre_hand.prime().value());
    CardListList llst;
    for (const Card& c : lst)
    {
        llst.push_back(CardList(1, c));
    }
    push_to_front(llst);
}

void Hand_Hinter::process_type_A_plus()
{
    process_type_A_AA_AAA_plus();
}

void Hand_Hinter::process_type_AA()
{
    CardListList lst = Hinter_Helper::find_BB_by_cmap(m_cmap, m_pre_hand.prime().value());
    if (lst.empty())
        return;

    //take out double Joker
    if (lst.back().front().value() == Card::V_joker)
    {
        lst.pop_back();
    }
    push_to_front(lst);
//    process_type_A_AA_plus(); // 这个函数也可以，只是提示顺序不是很合理
}

void Hand_Hinter::process_type_AA_plus()
{
    process_type_A_AA_AAA_plus();
}

void Hand_Hinter::process_type_A_AA_AAA_plus()
{
    CardListList ret;
    size_t type_size = m_pre_hand.type_size();
    size_t prime_size = m_pre_hand.prime_size();
    Card::Value min_prime = static_cast<Card::Value>(m_pre_hand.prime().value()-type_size+1);
    CardListList groups = Hinter_Helper::slice_to_group(m_cmap, min_prime, prime_size);
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
    push_to_front(ret);
}

void Hand_Hinter::process_type_AAA()
{
    push_to_front(Hinter_Helper::find_AAA_by_cmap(m_cmap, m_pre_hand.prime().value()));
}

void Hand_Hinter::process_type_AAA_plus()
{
    process_type_A_AA_AAA_plus();
}

void Hand_Hinter::process_type_AAAB()
{
    size_t type_size = m_pre_hand.type_size();
    Card::Value min_prime = static_cast<Card::Value>(m_pre_hand.prime().value()-type_size+1);
    CardListList groups = Hinter_Helper::slice_to_group(m_cmap, min_prime, 3);

    //first AAA
    CardListList a3s;
    for (const CardList& lst : groups)
    {
        if (lst.size() < type_size*3) continue;

        CardList::const_iterator beg = lst.cbegin();
        CardList::const_iterator end = beg;
        std::advance(end, type_size*3);
        for (; end!=lst.cend();
             std::advance(beg, 3), std::advance(end, 3))
        {
            a3s.push_back(CardList(beg, end));
        }
        a3s.push_back(CardList(beg, end));
    }

    CardListList ret;
    // second find type_size B
    if (a3s.size() == 1)
    {
        const CardList& a3 = a3s.front();
        ValueMap m = m_cmap;
        Hinter_Helper::remove_map_same_value(m, a3, 3, type_size);
        CardListList bs = Hinter_Helper::get_left_N(m, type_size);
        for (const CardList& b : bs)
        {
            CardList a3b = a3;
            push_back(a3b, b);
            sort(a3b);
            ret.push_back(a3b);
        }
    }
    else // multi AAA
    {
        for (const CardList& a3 : a3s)
        {
            ValueMap m = m_cmap;
            Hinter_Helper::remove_map_same_value(m, a3, 3, type_size);
            CardListList bs = Hinter_Helper::get_left_N(m, type_size);
            Q_ASSERT(bs.size() >= type_size);
            bs.resize(type_size);
            CardList a3b = a3;
            for(const CardList& b : bs)
            {
                push_back(a3b, b);
            }
            ret.push_back(a3b);
        }
    }
    push_to_front(ret);
}

void Hand_Hinter::process_type_AAABB()
{
    size_t type_size = m_pre_hand.type_size();
    Card::Value min_prime = static_cast<Card::Value>(m_pre_hand.prime().value()-type_size+1);
    CardListList groups = Hinter_Helper::slice_to_group(m_cmap, min_prime, 3);

    //first AAA
    CardListList a3s;
    for (const CardList& lst : groups)
    {
        if (lst.size() < type_size*3) continue;

        CardList::const_iterator beg = lst.cbegin();
        CardList::const_iterator end = beg;
        std::advance(end, type_size*3);
        for (; end!=lst.cend();
             std::advance(beg, 3), std::advance(end, 3))
        {
            a3s.push_back(CardList(beg, end));
        }
        a3s.push_back(CardList(beg, end));
    }

    CardListList ret;
    // second find type_size B
    if (a3s.size() == 1)
    {
        const CardList& a3 = a3s.front();
        ValueMap m = m_cmap;
        Hinter_Helper::remove_map_same_value(m, a3, 3, type_size);
        CardListList bbs = Hinter_Helper::find_BB_by_cmap(m, Card::V_none);
        for (const CardList& bb : bbs)
        {
            CardList a3bb = a3;
            push_back(a3bb, bb);
            sort(a3bb);
            ret.push_back(a3bb);
        }
    }
    else // multi AAA
    {
        for (const CardList& a3 : a3s)
        {
            ValueMap m = m_cmap;
            Hinter_Helper::remove_map_same_value(m, a3, 3, type_size);
            CardListList bbs = Hinter_Helper::find_BB_by_cmap(m, Card::V_none);
            if (bbs.size() >= type_size)
            {
                bbs.resize(type_size);
                CardList a3bb = a3;
                for(const CardList& bb : bbs)
                {
                    push_back(a3bb, bb);
                }
                ret.push_back(a3bb);
            }
        }
    }
    push_to_front(ret);
}

void Hand_Hinter::process_type_AAAABC()
{
    // first find AAAA;
    CardListList lst = Hinter_Helper::find_AAAA_by_cmap(m_cmap, m_pre_hand.prime().value());
    if (lst.empty()) // no AAAA
        return ;

    CardListList a42;
    //second find BC
    if (lst.size() == 1)
    {
        const CardList& a4 = lst.front();
        ValueMap left = m_cmap;
        Hinter_Helper::remove_map_same_value(left, a4, 4, 1);
        CardListList all_bc = Hinter_Helper::get_left_N(left, 2);

        for (const CardList& bc : all_bc)
        {
            Q_ASSERT(bc.size() == 2);
            CardList l = a4;
            push_back(l, bc);
            sort(l);
            a42.push_back(l);
        }
    }
    else // multi AAAA
    {
        for (const CardList& a4 : lst)
        {
            ValueMap left = m_cmap;
            Hinter_Helper::remove_map_same_value(left, a4, 4, 1);
            CardListList bcs = Hinter_Helper::get_left_N(left, 2);
            Q_ASSERT(!bcs.empty());
            CardList a4bc = a4;
            push_back(a4bc, bcs.front());
            sort(a4bc);
            a42.push_back(a4bc);
        }
    }
    push_to_front(a42);
}

void Hand_Hinter::process_type_AAAABBCC()
{
    // first find AAAA;
    CardListList lst = Hinter_Helper::find_AAAA_by_cmap(m_cmap, m_pre_hand.prime().value());
    if (lst.empty()) // no AAAA
        return ;

    CardListList a422;
    // find BBCC
    if (lst.size() == 1)
    {
        const CardList& a4 = lst.front();
        ValueMap left = m_cmap;
        Hinter_Helper::remove_map_same_value(left, a4, 4, 1);
        CardListList all_bbcc = Hinter_Helper::find_BBCC_by_cmap(left);
        for (const CardList& bbcc : all_bbcc)
        {
            CardList l = a4;
            push_back(l, bbcc);
            sort(l);
            a422.push_back(l);
        }
    }
    else // multi AAAA
    {
        for (const CardList& a4 : lst)
        {
            ValueMap left = m_cmap;
            Hinter_Helper::remove_map_same_value(left, a4, 4, 1);
            CardListList bbs = Hinter_Helper::find_BB_by_cmap(left, Card::V_none);
            if (bbs.size() >= 2)
            {
                CardList bbcc = a4;
                bbs.resize(2);
                push_back(bbcc, bbs.front());
                push_back(bbcc, bbs.back());
                sort(bbcc);
                a422.push_back(bbcc);
            }
        }
    }
    push_to_front(a422);
}

void Hand_Hinter::push_to_front(const CardListList &lst)
{
    for (const CardList& l : lst)
    {
        m_hint_queue.push(l);
    }
}

void Hand_Hinter::add_bomb_to_end()
{
    Card::Value v = Card::V_none;
    if (m_pre_hand.type() == Hand_Info::Bomb)
    {
        v = m_pre_hand.prime().value();
    }

    CardListList bombs = Hand_Helper::find_all_bomb(m_cmap, v);
    for (const CardList& b : bombs)
    {
        m_hint_queue.push(b);
    }
}


