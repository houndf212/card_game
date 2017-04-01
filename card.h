#ifndef CARD_H
#define CARD_H

#include "card_color.h"
#include "card_value.h"

class Card
{
public:
    constexpr Card(Card_Color color = Card_Color::None,
         Card_Value value = Card_Value::V_none)
        :m_color(color), m_value(value)
    {

    }

    bool isValid() const
    {
        return m_color != Card_Color::None
                && m_value != Card_Value::V_none;
    }

    void setColor(Card_Color color)
    {
        m_color = color;
    }
    void setValue(Card_Value value)
    {
        m_value = value;
    }

    Card_Color color() const
    {
        return m_color;
    }
    Card_Value value() const
    {
        return m_value;
    }

private:
    Card_Color m_color;
    Card_Value m_value;
};

#endif // CARD_H
