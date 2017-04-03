#include "deck.h"
#include <QtGlobal>

Deck::Deck()
{

}

bool Deck::insert(const Card &card)
{
    return m_cards.insert(card).second;
}

bool Deck::contains(const Card &card) const
{
    return m_cards.find(card) != m_cards.cend();
}

