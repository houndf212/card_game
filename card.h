#ifndef CARD_H
#define CARD_H
#include <QtCore>

class Card
{
    Q_GADGET
public:
    enum Color
    {
        C_none,
        diamond,
        club,
        heart,
        spade,
        black_joker,
        red_joker,
    };
    Q_ENUM(Color)

    enum Value
    {
        V_none = 0,
        V_3 = 1,
        V_4,
        V_5,
        V_6,
        V_7,
        V_8,
        V_9,
        V_10,
        V_jack,
        V_queen,
        V_king,
        V_ace,
        V_2 = V_ace+2, //用+2跳过检验连续
        V_joker = V_2+2,
    };
    Q_ENUM(Value)
public:
    Card(Card::Color color = Card::C_none,
         Card::Value value = Card::V_none)
        :m_color(color), m_value(value)
    {

    }

    bool isValid() const
    {
        return m_color != Card::C_none
                && m_value != Card::V_none;
    }

    Card::Color color() const
    {
        return m_color;
    }
    Card::Value value() const
    {
        return m_value;
    }

private:
    Card::Color m_color;
    Card::Value m_value;
};

QDebug operator<<(QDebug os, const Card& card);
#include "card_compare.h"

#endif // CARD_H
