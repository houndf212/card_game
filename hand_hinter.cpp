#include "hand_hinter.h"

void Hand_Hinter::set_hand(const std::set<Card> &cards, const Hand_Info &pre_hand)
{
    Q_ASSERT(!cards.empty());
    m_cards = cards;
    m_countMap = Hand_Helper::count_value(cards);

    m_pre_hand = pre_hand;
    process_data();
}

