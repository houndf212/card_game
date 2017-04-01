#ifndef CARD_DECK_H
#define CARD_DECK_H
#include "init_deck.h"

class Card_Deck
{
public:
    Card_Deck();
    void reset();
    void shuffle();
    Card get_card(int index) const;
private:
    array<Card, DECK_SIZE> m_array;
};

#endif // CARD_DECK_H
