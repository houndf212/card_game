#include "card_deck.h"
#include <algorithm>
#include <qglobal.h>
#include <ctime>

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
