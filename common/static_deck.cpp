#include "static_deck.h"
#include <ctime>
#include <algorithm>
#include <QtGlobal>

std::array<Card, Static_Deck::SIZE> Static_Deck::INIT_DECK;
Static_Deck::CardIndex Static_Deck::CARD_INDEX;

void Static_Deck::init()
{
    //seed rand;
    std::srand(std::time(0));

    int index = 0;

    int start_val = Card::V_3;
    int end_val = Card::V_ace;

    Q_ASSERT(end_val > start_val);
    for (; start_val <= end_val; ++start_val)
    {
        int start_col = Card::diamond;
        int end_col = Card::spade;

        Q_ASSERT(end_col > start_col);
        for (; start_col <= end_col; ++start_col)
        {
            Card c(static_cast<Card::Color>(start_col), static_cast<Card::Value>(start_val));
            CARD_INDEX.insert({c, index});
            INIT_DECK[index++] = c;
        }
    }

    int start_col = Card::diamond;
    int end_col = Card::spade;

    Q_ASSERT(end_col > start_col);
    for (; start_col <= end_col; ++start_col)
    {
        Card c(static_cast<Card::Color>(start_col), Card::V_2);
        CARD_INDEX.insert({c, index});
        INIT_DECK[index++] = c;
    }

    Card black_joker(Card::black_joker, Card::V_joker);
    CARD_INDEX.insert({black_joker, index});
    INIT_DECK[index++] = black_joker;

    Card red_joker(Card::red_joker, Card::V_joker);
    CARD_INDEX.insert({red_joker, index});
    INIT_DECK[index++] = red_joker;

    Q_ASSERT(index = SIZE);
}

const std::array<Card, Static_Deck::SIZE> &Static_Deck::get_init()
{
    return INIT_DECK;
}

Card Static_Deck::index_card(int index)
{
    Q_ASSERT(0<=index && static_cast<size_t>(index)<INIT_DECK.size());
    return INIT_DECK.at(index);
}

int Static_Deck::card_index(const Card &card)
{
    CardIndex::const_iterator p = CARD_INDEX.find(card);
    Q_ASSERT(p != CARD_INDEX.cend());
    return p->second;
}
