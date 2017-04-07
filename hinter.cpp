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
            process_type_AAA();
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
    CardListList lst = Hinter_Helper::find_B_by_map(m_cmap, m_pre_hand.prime().value());

    for (const CardList& l : lst)
    {
        m_hint_queue.push(l);
    }
}

void Hand_Hinter::process_type_A_plus()
{

}

void Hand_Hinter::process_type_AA()
{
    CardListList lst[3]; // 0-2,1-3,2-4
    for (const Hand_Helper::ValuePair& p : m_cmap)
    {
        if (p.first.value() > m_pre_hand.prime().value()
                && p.second.size()>=2)
        {
            CardList l;
            l.push_back(p.second.at(0));
            l.push_back(p.second.at(1));
            size_t size = p.second.size();
            Q_ASSERT(2<=size && size<=4);
            lst[size-2].push_back(l);
        }
    }

    //take out double Joker
    if (lst[0].back().front().value() == Card::V_joker)
    {
        lst[0].pop_back();
    }

    for (const CardListList& l : lst)
    {
        for (const CardList& kl : l)
        {
            m_hint_queue.push(kl);
        }
    }

}

void Hand_Hinter::process_type_AA_plus()
{

}

void Hand_Hinter::process_type_AAA()
{

}

void Hand_Hinter::process_type_AAAB()
{

}

void Hand_Hinter::process_type_AAABB()
{

}

void Hand_Hinter::process_type_AAAABC()
{
    // first find AAAA;
    CardListList lst;
    for (const Hand_Helper::ValuePair& p : m_cmap)
    {
        if (p.first.value() > m_pre_hand.prime().value()
                && p.second.size() == 4)
        {
            lst.push_back(p.second);
        }
    }

    //second find BC
    for (CardListList::const_iterator it=lst.begin(); it!=lst.end(); ++it)
    {
        CardList all = Hinter_Helper::remove_list(m_cards, *it);
    }

}

void Hand_Hinter::process_type_AAAABBCC()
{

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


