#ifndef HAND_HINTER_H
#define HAND_HINTER_H
#include "hand_info.h"
#include "hand_helper.h"

//由于提示类有点复杂，这里采用分不同类型处理
class Hand_Hinter
{
protected:
    Hand_Hinter() {}
public:
    virtual ~Hand_Hinter() {}
public:
    void set_hand(const std::set<Card>& cards, const Hand_Info& pre_hand);
    virtual Hand_Info next_hint() = 0;
protected:
    virtual process_data() = 0;
protected:
    std::set<Card> m_cards;
    Hand_Helper::CountMap m_countMap;
    Hand_Info m_pre_hand;
};

#endif // HAND_HINTER_H
