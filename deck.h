#ifndef DECK_H
#define DECK_H
#include <set>
#include "card.h"

class Deck
{
public:
    Deck();
    bool insert(const Card& card);
    bool contains(const Card& card) const;
    int size() const { return m_cards.size(); }
private:
    std::set<Card> m_cards;
};

#endif // DECK_H
