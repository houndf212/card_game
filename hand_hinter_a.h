#ifndef HAND_HINTER_A_H
#define HAND_HINTER_A_H
#include <queue>
#include "hand_hinter.h"

// 单张
class Hand_Hinter_A : public Hand_Hinter
{
public:
    Hand_Hinter_A();
    Hand_Info next_hint() override;
protected:
    void process_data() override;
    std::queue<Card> m_hint_queue;
};

#endif // HAND_HINTER_A_H
