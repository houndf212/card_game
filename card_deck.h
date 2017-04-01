#ifndef CARD_DECK_H
#define CARD_DECK_H
#include <array>
#include "card.h"

using std::array;

class Card_Deck
{
public:
    static constexpr int DECK_SIZE = 54;
    static void init();
    static const array<Card, DECK_SIZE>& get_init();
private:
    static array<Card, DECK_SIZE> INIT_DECK;
public:
    Card_Deck();
    void reset();
    void shuffle();
    Card get_card(int index) const;
private:
    array<Card, DECK_SIZE> m_array;
private:

};

#endif // CARD_DECK_H
