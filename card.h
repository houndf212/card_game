#ifndef CARD_H
#define CARD_H
#include <QtCore>

class Card
{
    Q_GADGET
public:
    enum Color
    {
        none,
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
        V_none,
        V_3,
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
        V_2,
        V_black_joker,
        V_red_joker,
    };
    Q_ENUM(Value)
public:
    Card(Card::Color color = Card::Color::none,
         Card::Value value = Card::Value::V_none)
        :m_color(color), m_value(value)
    {

    }

    bool isValid() const
    {
        return m_color != Card::Color::none
                && m_value != Card::Value::V_none;
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
