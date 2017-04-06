#ifndef HAND_HELPER_H
#define HAND_HELPER_H

#include <set>
#include "card.h"

namespace Hand_Helper
{
typedef std::map<Card, int, Value_Less> CountMap;

CountMap count_value(const std::set<Card>& cards);

int find_count_size(const CountMap& cmap, int count, bool can_over_flow);

std::pair<int, Card> find_max_group_by_count(const CountMap& cmap, int count, bool can_over_flow);
}

#endif // HAND_HELPER_H
