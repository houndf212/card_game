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

    //first set invalid
    m_type = Type::Invalid;

    //先处理小size 情况， 可以让后面处理变得简单， 也可以提高速度
    int size = m_cards.size();
    switch (size)
    {
    case 0:
        set_null();
        break;
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

void Hand_Info::set_null()
{
    *this = Hand_Info();
}

void Hand_Info::hand_size_1()
{
    m_type = Type::A;
    m_type_size = 1;
    m_prime = m_cards.cbegin()->value();
    m_prime_size = 1;
}

void Hand_Info::hand_size_2()
{
    auto iter = m_cards.cbegin();
    Card card1 = *iter;
    Card card2 = *(++iter);

    if (card1.value() == Card::V_black_joker)
    {
        Q_ASSERT(card2.value() == Card::V_red_joker);
        m_type = Type::Bomb;
        m_type_size = 1;
        m_prime = card1.value();
        m_prime_size = 2;
    }
    else if (value_equal(card1, card2))
    {
        m_type = Type::AA;
        m_type_size = 1;
        m_prime = card1.value();
        m_prime_size = 2;
    }
}

void Hand_Info::hand_size_3_plus()
{
    const int card_size = m_cards.size();

    count_value();
    find_prime();
//    m_type_size = find_count_size(m_prime_size);

    if (m_type_size>1 && !check_continue())
    {
//        qDebug() << "check contine faild, invalid";
        return;
    }

    // 现在来确定属于什么类型

    switch (m_prime_size)
    {
    case 1: // 56789
    {
        if (card_size >= 5 && card_size == m_type_size) // 56789
        {
            m_type = Type::A;
        }
    }
        break;
    case 2: // 334455
    {
        if (m_type_size>=3 && card_size == 2*m_type_size) // 33445566
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
        else if (card_size == 4*m_type_size) //3334 333444?? 333444555???
        {
            m_type = Type::AAAB;
        }
        else if(card_size == 5*m_type_size
                && find_count_size(1) == 0) //33344 3334445566 3334445555
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
                 && find_count_size(1) == 0
                 && find_count_size(3) ==0) //33335566 33335555 333344445555889999
        {
            m_type = Type::AAAABBCC;
        }
    }
        break;
    default:
        Q_ASSERT(false);
        break;
    }
    // 如果是叠加牌型，那么肯定不含 2 和 王
    if (type()!=Type::Invalid && type_size()>1)
    {
        Q_ASSERT(prime() < Card::Value::V_2);
    }
    Q_ASSERT(prime_size()==1 || prime_size()==2 || prime_size()==3 || prime_size()==4);
}

void Hand_Info::count_value()
{
    for (auto c : m_cards)
    {
        m_countMap[c]++;
    }
    // 特殊处理同时含有大小王，把大小王 当作一对大王处理，以便 333+joker+joker 可以出牌
    auto p1 = m_countMap.find({Card::black_joker, Card::V_black_joker});
    if (p1!=m_countMap.cend())
    {
        auto p2 = m_countMap.find({Card::red_joker, Card::V_red_joker});
        if (p2!=m_countMap.cend())
        {
            Q_ASSERT(p2->second == 1);
            p2->second = 2;
            m_countMap.erase(p1);
        }
    }
}

void Hand_Info::find_prime()
{
    // TODO 怎么处理这种情况 33446666+77778888

    int cards_size = m_cards.size();
    int count_size = m_countMap.size();

    if (cards_size == count_size) // or find_count_size(1) == cards_size  => A+
    {
        Q_ASSERT(find_count_size(1) == cards_size);
        std::tie(m_type_size, m_prime) = find_max_group_by_count(1);
        m_prime_size = 1;
        return;
    }

    if (find_count_size(3) == 0 &&find_count_size(4) ==0) // 345 34566 335566 33445566
    {
        Q_ASSERT(find_count_size(2) != 0);
        std::tie(m_type_size, m_prime) = find_max_group_by_count(2);
        m_prime_size = 2;
        return;
    }

    if (find_count_size(3) > find_count_size(4))
    {
        std::tie(m_type_size, m_prime) = find_max_group_by_count(3);
        m_prime_size = 3;
        return;
    }
    std::tie(m_type_size, m_prime) = find_max_group_by_count(4);
    m_prime_size = 4;
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

std::pair<int, Card::Value> Hand_Info::find_max_group_by_count(int count) const
{
    std::map<int, Card::Value> c_map;

    Card::Value val = Card::V_none;
    int c_size = 0;

    c_map[c_size] = val;

    for (auto p : m_countMap)
    {
        if (p.second == count)
        {
            //3334455566677788 == 3567
            if (val+1 == p.first.value()) // none+1 = v_3
            {
                val = p.first.value();
                ++c_size;
            }
            else // v_3 +1 != v_5
            {
                c_map[c_size] = val; // push 1, v_3
                val = p.first.value(); //val = 5
                c_size = 1;
            }

        }
    }
    c_map[c_size] = val;
    qDebug() << *c_map.crbegin();
    return *c_map.crbegin();
}

bool Hand_Info::check_continue() const
{
    if (m_prime >= Card::Value::V_2)
        return false;

    return true;
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
