#include "hand_info.h"
#include <algorithm>
#include <map>
#include <QtGlobal>
#include <QDebug>

Hand_Info::Hand_Info()
    :m_type(Type::Null)
    ,m_type_size(0)
    ,m_prime(Card::Value::V_none)
    ,m_prime_size(0)
    ,m_countMap(&value_less)
{

}

void Hand_Info::set_cards(const std::set<Card> &vec)
{
    m_cards = vec;

    if (m_cards.empty())
    { set_null(); }
    else
    { hand_size_1_plus(); }
}

void Hand_Info::set_null()
{
    *this = Hand_Info();
}

void Hand_Info::hand_size_1_plus()
{
    const int card_size = m_cards.size();

    // TODO 怎么处理这种情况 333444kkkk
    count_value();
    find_prime();
    m_type_size = find_count_size(m_prime_size);

    // 这里需要特殊处理 双王情况
    if (card_size == 2
            && m_prime == Card::V_red_joker
            && m_cards.cbegin()->value() == Card::V_black_joker)
    {
        m_type = Type::Bomb;
        m_type_size = 1;
        return;
    }

    // TODO 怎么处理这种情况 333444555jjj
    if (m_type_size>1 && !check_continue())
    {
//        qDebug() << "check contine faild, invalid";
        m_type = Type::Invalid;
        return;
    }

    // 现在来确定属于什么类型

    // first set invalid
    m_type = Type::Invalid;

    switch (m_prime_size)
    {
    case 1: // 3 or 56789
    {
        if (card_size == 1 || card_size >= 5) // 3 or 56789
        {
            m_type = Type::A;
        }
    }
        break;
    case 2: // 33 or 334455
    {
        if (card_size == 2) // 33
        {
            m_type = Type::AA;
        }
        else if (m_type_size>=3 && card_size == 2*m_type_size) // 33445566
        {
            m_type = Type::AA;
        }
    }
        break;
    case 3: // 333 3334 33344 333444 and ++
    {
        if (card_size == 3*m_type_size) //333 333444 333444555
        {
            m_type = Type::AAA;
        }
        else if (card_size == 4*m_type_size) //3334 333444?? 333444555??? //TODO 333+jokerjoker
        {
            m_type = Type::AAAB;
        }
        else if(card_size == 5*m_type_size
                && find_count_size(2) == m_type_size) //33344 3334445566 333444555667799
        {
            m_type = Type::AAABB;
        }
    }
        break;
    case 4: // 3333 333345 333344 33334455
    {
        if (card_size == 4) //特殊处理炸弹
        {
            m_type = Type::Bomb;
        }
        else if (card_size == 4*m_type_size)
        {
            m_type = Type::AAAA;
        }
        else if (card_size == 6*m_type_size) //333345+
        {
            m_type = Type::AAAABC;
        }
        else if (card_size == 8*m_type_size
                 && find_count_size(2) == 2*m_type_size) //33555599
        {
            m_type = Type::AAAABBCC;
        }
    }
        break;
    default:
        m_type = Type::Invalid;
        Q_ASSERT(false);
        break;
    }
    // 如果是叠加牌型，那么肯定不含 2 和 王
    if (m_type!=Type::Invalid && m_type_size>1)
    {
        Q_ASSERT(m_prime < Card::Value::V_2);
    }
}

void Hand_Info::count_value()
{
    for (auto c : m_cards)
    {
        m_countMap[c]++;
    }
}

void Hand_Info::find_prime()
{
    m_prime_size = 0;
    m_prime = Card::Value::V_none;
    for (auto p : m_countMap)
    {
        if (p.second>=m_prime_size)
        {
            m_prime_size = p.second;
            m_prime = p.first.value();
        }
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

Card::Value Hand_Info::find_min_value_by_count(int count) const
{
    for (auto p : m_countMap)
    {
        if (p.second == count)
        {
            return p.first.value();
        }
    }
    Q_ASSERT(false);
    return Card::Value::V_none;
}

bool Hand_Info::check_continue() const
{
    if (m_prime >= Card::Value::V_2)
        return false;

    Card::Value start = find_min_value_by_count(m_prime_size);
    return m_prime - start + 1 == m_type_size;
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
            //Q_ASSERT(info1.size() == info2.size());
            return info1.prime() < info2.prime();
        }
        else
            return false;
    }

    // 不是同一类型
    return false;
}
