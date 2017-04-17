#ifndef HAND_HELPER_H
#define HAND_HELPER_H

#include "card.h"

namespace Hand_Helper
{


ValueMap count_value(const CardList &cards);

int find_count_size(const ValueMap& cmap, size_t count, bool can_over_flow);

std::pair<int, Card> find_max_group_by_count(const ValueMap& cmap, size_t count, bool can_over_flow);

CardListList find_all_bomb(const ValueMap& cmap, Card::Value floor);
}

#endif // HAND_HELPER_H
