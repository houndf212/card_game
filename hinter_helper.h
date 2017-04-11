#ifndef HINTER_HELPER_H
#define HINTER_HELPER_H
#include "card.h"
#include "hand_helper.h"

namespace Hinter_Helper
{
void remove_map_same_value(ValueMap &cmap, const CardList& lst, size_t prime_size, size_t type_size);
void remove_list_same_value(CardList& target, const CardList& m);

CardList find_B_by_cmap(const ValueMap& cmap, Card::Value floor);
CardListList find_BB_by_cmap(const ValueMap& cmap, Card::Value floor);

CardListList get_left_N(const ValueMap& cmap, size_t n);
CardList get_list_by_count(const ValueMap& cmap);
// ========================================
//这个函数过于复杂，基本上返回C(size, n)数量巨大 放弃这种方式
CardListList find_N_by_cmap(const ValueMap &cmap, int n);
CardListList find_BC_by_cmap(const ValueMap& cmap);
CardListList find_BBCC_by_cmap(const ValueMap& cmap);
void find_N_recursion(CardListList& all,
                              const ValueMap& cmap,
                              const CardList& lst,
                              int n);
// ========================================


CardListList find_AAA_by_cmap(const ValueMap& cmap, Card::Value floor);

CardListList find_AAAA_by_cmap(const ValueMap& cmap, Card::Value floor);

ValueMap get_map_greater_value_size(const ValueMap& cmap, Card::Value val, size_t prime_size);
CardListList slice_to_group(const ValueMap& cmap, Card::Value val,size_t type_size, size_t prime_size);
CardListList find_group(const CardListList& groups, size_t type_size, size_t prime_size);
bool is_bomb_list(const ValueMap& cmap, const CardList& lst);
}

#endif // HINTER_HELPER_H
