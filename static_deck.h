#ifndef STATIC_DECK_H
#define STATIC_DECK_H
#include <array>
#include <map>
#include "card.h"

class Static_Deck
{
public:
    static constexpr int SIZE = 54;
    static void init();
    static const std::array<Card, SIZE>& get_init();
    static Card index_card(int index);
    static int card_index(const Card& card);
private:
    static std::array<Card, SIZE> INIT_DECK;
    typedef std::map<Card, int, Card_Compare> CardIndex;
    static CardIndex CARD_INDEX;
};

#endif // STATIC_DECK_H
