#ifndef ONEHAND_H
#define ONEHAND_H
#include <vector>
#include "card.h"
#include "hand_type.h"
using std::vector;

class OneHand
{
public:
    OneHand(); //null hand
    OneHand(const vector<Card>& vec);
private:
    vector<Card> m_cards;
    Hand_Type m_hand_type;
};

#endif // ONEHAND_H
