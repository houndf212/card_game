#ifndef HINTER_H
#define HINTER_H
#include <queue>
#include "hand_info.h"
#include "hand_helper.h"

//由于提示类有点复杂，这里采用分不同类型处理
class Hand_Hinter
{
public:
    int size() { return m_hint_queue.size(); }
    CardList next_hint();
    void set_hand(const CardList& cards, const CardList& pre_hand);
private:
    void process_type_Null();
    void process_type_A();
    void process_type_A_plus();

    void process_type_AA();
    void process_type_AA_plus();

    void process_type_AAA();
    void process_type_AAAB();
    void process_type_AAABB();

    void process_type_AAAABC();
    void process_type_AAAABBCC();

    void push_to_front(const CardListList& lst);
    void add_bomb_to_end();
private:

private:
    CardList m_cards;
    ValueMap m_cmap;
    Hand_Info m_pre_hand;
    std::queue<CardList> m_hint_queue;
};

#endif // HINTER_H
