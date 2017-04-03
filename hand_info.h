#ifndef HAND_INFO_H
#define HAND_INFO_H
#include <set>
#include "card.h"

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
        AAAA,       //33333 (2+)
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
    Card::Value prime() const { return m_prime; }
    int prime_size() const { return m_prime_size; }
private:
    void set_null();
    void hand_size_1_plus();
private:
    void count_value();
    void find_prime();
    int find_count_size(int count) const;
    Card::Value find_min_value_by_count(int count) const;
    bool check_continue() const;
private:
    Type m_type;           // 属于那种出牌类型
    int m_type_size;            // 出牌类型的长度
    Card::Value m_prime;   // 主元素值
    int m_prime_size;           // 主元素长度
    std::set<Card> m_cards;
    typedef std::map<Card, int, Card_Compare> CountMap;
    CountMap m_countMap;
};

bool operator < (const Hand_Info& info1, const Hand_Info& info2);

#endif // HAND_INFO_H