#include "card.h"
#include <QDebug>
#include <QMetaEnum>

QDebug operator<<(QDebug os, const Card& card)
{
    QMetaEnum val = QMetaEnum::fromType<decltype(card.value())>();
    QMetaEnum col = QMetaEnum::fromType<decltype(card.color())>();
    return os<<"["<<val.valueToKey(card.value())<<
               ","<<col.valueToKey(card.color())<<"]";
}

