#ifndef HINTER_HELPER_H
#define HINTER_HELPER_H
#include "card.h"
#include "hand_helper.h"

namespace Hinter_Helper
{
ValueMap remove_map(const ValueMap& cmap, const CardList& lst);
CardList remove_list(const CardList& source, const CardList& m);
CardList remove(const CardList& source, const Card &card);

CardListList find_B_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_B(const CardList& cards);

CardListList find_BB_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BB(const CardList& cards);
CardListList find_BC(const CardList& cards);
CardListList find_BBCC(const CardList& cards);
}

#endif // HINTER_HELPER_H
