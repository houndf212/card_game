#include "hand_info.h"
#include <algorithm>
#include <map>
#include <QtGlobal>
#include <QDebug>

Hand_Info::Hand_Info()
    :m_type(Type::Null)
    ,m_type_size(0)
    ,m_prime(Card::C_none, Card::V_none)
    ,m_prime_size(0)
    ,m_adjust_prime_size(0)
    ,m_countMap(&value_less)
{

}

void Hand_Info::set_cards(const std::set<Card> &vec)
{
    if (vec.empty())
        return;

    m_cards = vec;

    //first set invalid
    m_type = Type::Invalid;

    //先处理小size 情况， 可以让后面处理变得简单， 也可以提高速度
    switch (m_cards.size())
    {
    case 1:
        hand_size_1();
        break;
    case 2:
        hand_size_2();
        break;
    default:
        hand_size_3_plus();
    }
}

void Hand_Info::hand_size_1()
{
    m_type = Type::A;
    m_type_size = 1;
    m_prime = *m_cards.cbegin();
    m_prime_size = 1;
}

void Hand_Info::hand_size_2()
{
    auto iter = m_cards.cbegin();
    Card card1 = *iter;
    Card card2 = *(++iter);

    if (card1.value() == Card::V_joker)
    {
        Q_ASSERT(card2.value() == Card::V_joker);
        m_type = Type::Bomb;
        m_type_size = 1;
        m_prime = card2;
        m_prime_size = 2;
    }
    else if (value_equal(card1, card2))
    {
        m_type = Type::AA;
        m_type_size = 1;
        m_prime = std::max(card1, card2);
        m_prime_size = 2;
    }
}

void Hand_Info::hand_size_3_plus()
{
    // *******************************************************************
    //  54443333 -> 53+444333
    //  333344455556 ->333444555+356
    // 上述问题2个解决方案
    // 1 出现4个必须是 4带1或者4带2，
    // 2 规定 4带不能重复 只能6张牌或者8张牌, 即是说 AAAABC AAAABBCC 没有+
    // 那么在处理3带的时候在特殊化处理， 添加上4个可以回变成3个，那么只能是AAAB+型
    //********************************************************************
    // 总体来说 2 比较科学 而且 在 做 "提示" 功能的时候比较容易实现
    //********************************************************************

    count_value();

    const int cards_size = m_cards.size();
    const int count_size = m_countMap.size();

    if (cards_size == count_size) // 全是单牌
    {
        if (cards_size >= 5) // 必须是5张以上
        {
            Card first = *m_cards.cbegin();
            Card end = *m_cards.crbegin();
            if (cards_size == end.value()-first.value()+1) //连续
            {
                m_type = Type::A;
                m_type_size = cards_size;
                m_prime = end;
                m_prime_size = 1;
            }
        }
        return;
    }

    if (find_count_size(3) == 0 && find_count_size(4) == 0) // 最大含有count为2
    {
        Q_ASSERT(find_count_size(2) != 0);
        if (cards_size >= 6 && cards_size == 2*count_size) //全是对子，且大于3对
        {
            Card first = *m_cards.cbegin();
            Card end = *m_cards.crbegin();
            if (count_size == end.value()-first.value()+1) //连续
            {
                m_type = Type::AA;
                m_type_size = count_size;
                m_prime = end;
                m_prime_size = 2;
            }
        }
        return;
    }

    if (find_count_size(4) == 1) // 含有count为4 只能是 4带2 或者4带2对，且不能叠加，所以可以先处理
    {
        if (cards_size == 4)
        {
            m_type = Type::Bomb;
            m_type_size = 1;
            m_prime = *m_cards.crbegin();
            m_prime_size = 4;
            return;
        }

        if (cards_size == 6) // 只能是 4带2
        {
            m_type = Type::AAAABC;
            m_type_size = 1;
            m_prime = *m_cards.crbegin();
            m_prime_size = 4;
            return;
        }

        if(cards_size == 8
                &&find_count_size(1) == 0
                && find_count_size(3) ==0) // 4带2对
        {
            m_type = Type::AAAABBCC;
            m_type_size = 1;
            m_prime = *m_cards.crbegin();
            m_prime_size = 4;
            return;
        }

        // 这里不return的原因是 可能存在这类情况 33344445 =》 333444+45
    }

    // else 只能是3带了


    std::tie(m_type_size, m_prime) = find_possible_max_group_by_count(3, true);
    if (m_type_size > 0)
    {
        if (cards_size == 3*m_type_size) //333 333444 333444555
        {
            m_type = Type::AAA;
            m_prime_size = 3;
            return;
        }
        else //3334 333444?? 333444555??? 以及特殊情况 =》 2333+444555666777
        {
            // card_size = 4*m_type_size
            // card_size = 4*(m_type_size-1) ==
            int test = m_type_size;
            do
            {
                if (cards_size == 4*test)
                {
                    m_type = Type::AAAB;
                    m_adjust_prime_size = m_type_size - test;
                    m_type_size = test;
                    return;
                }

                if (cards_size == 5*test && find_count_size(1) == 0)
                {
                    m_type = Type::AAABB;
                    m_adjust_prime_size = m_type_size - test;
                    m_type_size = test;
                    return;
                }
                --test;
            }
            while(cards_size <= 5*test);
        }
    }
    Q_ASSERT(m_type == Type::Invalid);
}

void Hand_Info::count_value()
{
    for (auto c : m_cards)
    {
        m_countMap[c]++;
    }
}

int Hand_Info::find_count_size(int count) const
{
    int size = 0;
    for (auto p : m_countMap)
    {
        if (p.second == count)
            ++size;
    }
    return size;
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
std::pair<int, Card> Hand_Info::find_possible_max_group_by_count(int count, bool can_over_flow) const
{
    std::map<int, Card> c_map;

    Card val(Card::C_none, Card::V_none);
    int c_size = 0;

    c_map[c_size] = val;

    for (auto p : m_countMap)
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

bool operator < (const Hand_Info &info1, const Hand_Info &info2)
{
    // 0 必须是 valid 才有比较的意义
    Q_ASSERT(info1.isValid() && info2.isValid());

    // 1 null  小于任何
    if (info1.type() == Hand_Info::Null)
        return true;

    // 2 非炸弹小于任何炸弹
    if (info1.type()!=Hand_Info::Bomb && info2.type() == Hand_Info::Bomb)
        return true;

    // 3 相同类型
    if (info1.type() == info2.type())
    {
        if (info1.type_size() == info2.type_size())
        {
            // 双王的时候 下面assert 不成立
            // Q_ASSERT(info1.size() == info2.size());
            // 双王的时候 value 一样
            if (info1.prime_size()==1)
            {
                Q_ASSERT(info1.type() == Hand_Info::A && info1.type_size()==1);
                if (info1.prime().color() == Card::red_joker)
                    return false;
                else if(info2.prime().color() == Card::red_joker)
                    return true;
            }

            return value_less(info1.prime(), info2.prime());
        }
        else
            return false;
    }

    // 不是同一类型
    return false;
}
