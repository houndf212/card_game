#include "card.h"


QDebug operator<<(QDebug os, const Card& card)
{
    return os<<"("<<card.value()<<","<<card.color()<<")";
}
