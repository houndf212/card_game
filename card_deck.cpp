#include "card_deck.h"
#include <algorithm>
#include <qglobal.h>
#include <ctime>

array<Card, Card_Deck::DECK_SIZE> Card_Deck::INIT_DECK;

void Card_Deck::init()
{
    int index = 0;
    int start_col = static_cast<int>(Card_Color::Diamond);
    int end_col = static_cast<int>(Card_Color::Spade);

    Q_ASSERT(end_col > start_col);

    for (; start_col <= end_col; ++start_col)
    {
        int start_val = static_cast<int>(Card_Value::V_3);
        int end_val = static_cast<int>(Card_Value::V_2);

        Q_ASSERT(end_val > start_val);
        for (; start_val <= end_val; ++start_val)
        {
            Card c(static_cast<Card_Color>(start_col), static_cast<Card_Value>(start_val));
            INIT_DECK[index++] = c;
        }
    }
    Card black_joker(Card_Color::Black_Joker, Card_Value::V_joker);
    INIT_DECK[index++] = black_joker;

    Card red_joker(Card_Color::Red_Joker, Card_Value::V_joker);
    INIT_DECK[index++] = red_joker;
    Q_ASSERT(index = DECK_SIZE);
}

const array<Card, Card_Deck::DECK_SIZE> &Card_Deck::get_init()
{
    return INIT_DECK;
}

Card_Deck::Card_Deck()
    :m_array(INIT_DECK)
{
    //seed rand;
    std::srand(std::time(0));
}

void Card_Deck::reset()
{
    m_array = INIT_DECK;
}

void Card_Deck::shuffle()
{
    std::random_shuffle(m_array.begin(), m_array.end());
}

Card Card_Deck::get_card(int index) const
{
    Q_ASSERT(0<=index && static_cast<size_t>(index)<m_array.size());
    return m_array.at(index);
}
