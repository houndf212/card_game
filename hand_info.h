#ifndef HAND_INFO_H
#define HAND_INFO_H
#include "hand_helper.h"

class Hand_Info
{
    Q_GADGET
public:
    enum  Type
    {
        Null,
        Invalid,    //不合法
        A,          //单张（1） 或者 连子（5+）
        AA,         //一对（1） 或者 连对（3+)
        AAA,        //333 （1+）
        AAAB,       //3337（1+）
        AAABB,      //3338 (1+)
        AAAABC,     //33333jk (1+) or 333344(1+)
        AAAABBCC,   //333337799 (1+) or 33334444
        Bomb,         //two joker 必定是black_joker+red_joker
    };
    Q_ENUM(Type)

public:
    Hand_Info();
    void set_cards(const std::set<Card> &vec);

    bool isValid() const { return m_type != Type::Invalid; }
    int size() const { return m_cards.size(); }
    Type type() const { return m_type; }
    int type_size() const { return m_type_size; }
    Card prime() const { return m_prime; }
    int prime_size() const { return m_prime_size; }
    bool adjust_size() const { return m_adjust_prime_size; }
private:
    void hand_size_1();
    void hand_size_2();
    void hand_size_3_plus();
private:
    Type m_type;                // 属于那种出牌类型
    int m_type_size;            // 出牌类型的长度
    Card m_prime;               // 主元素值
    int m_prime_size;           // 主元素长度
    int m_adjust_prime_size;              // 是否调整过prime_size
    std::set<Card> m_cards;
    Hand_Helper::CountMap m_countMap;
};

bool hand_less(const Hand_Info& info1, const Hand_Info& info2);

#endif // HAND_INFO_H
