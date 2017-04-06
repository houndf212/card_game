#include "hand_hinter_a.h"

Hand_Hinter_A::Hand_Hinter_A()
{

}

void Hand_Hinter_A::process_data()
{
    Q_ASSERT(m_pre_hand.type() == Hand_Info::A
             && m_pre_hand.type_size()==1
             && m_pre_hand.prime_size()==1);
}
