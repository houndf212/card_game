#ifndef HINTER_HELPER_H
#define HINTER_HELPER_H
#include "card.h"
#include "hand_helper.h"

namespace Hinter_Helper
{
void push_back(CardList& target, const CardList& lst);
void push_back_n(CardList& target, const CardList& lst, size_t size);

void remove_map(ValueMap &cmap, const CardList& lst);
void remove_list(CardList& target, const CardList& m);

CardList find_B_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BB_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BC_by_cmap(const ValueMap& cmap);

CardListList find_N_by_cmap(const ValueMap& cmap, int n);

CardListList find_BBCC_by_cmap(const ValueMap& cmap);

CardListList find_AAA_by_cmap(const ValueMap& cmap, Card::Value floor);

CardListList find_AAAA_by_cmap(const ValueMap& cmap, Card::Value floor);

ValueMap get_map_greater_value_size(const ValueMap& cmap, Card::Value val, size_t size);
CardListList slice_to_group(const ValueMap& cmap, Card::Value val, size_t size);
}

#endif // HINTER_HELPER_H
