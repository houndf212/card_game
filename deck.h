#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck
{
public:
    Deck();
    bool insert(const Card& card);
    bool contains(const Card& card) const;
    int size() const { return m_cards.size(); }
private:
    CardSet m_cards;
};

#endif // DECK_H
