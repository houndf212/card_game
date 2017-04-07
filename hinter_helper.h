#ifndef HINTER_HELPER_H
#define HINTER_HELPER_H
#include "card.h"
#include "hand_helper.h"

namespace Hinter_Helper
{
void remove_map(ValueMap &cmap, const CardList& lst);
void remove_list(CardList& target, const CardList& m);

CardList find_B_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BB_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BC_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BBCC_by_cmap(const ValueMap& cmap, Card::Value floor);
}

#endif // HINTER_HELPER_H
