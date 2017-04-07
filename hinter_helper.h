#ifndef HINTER_HELPER_H
#define HINTER_HELPER_H
#include "card.h"
#include "hand_helper.h"

namespace Hinter_Helper
{
CardList remove_in(const CardList& source, const Card &card);
CardListList find_B_by_map(const Hand_Helper::ValueMap& cmap, Card::Value val);
CardListList find_B(const CardList& cards);
CardListList find_BB(const Card& cards);
CardListList find_BC(const CardList& cards);
CardListList find_BBCC(const CardList& cards);
}

#endif // HINTER_HELPER_H
