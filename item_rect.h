#ifndef ITEM_RECT_H
#define ITEM_RECT_H
#include <QtCore>
#include <QGraphicsScene>
#include "card_item.h"

class Item_Rect
{
public:
    Item_Rect(const QLineF& rect, QGraphicsScene* scene);
    Card_Item* init(const Card& c, bool is_animate);

    bool contains(const Card& c) const;

    bool add(const Card& c, Card_Item* item);
    Card_Item* remove(const Card& c);

    CardList get_cards() const;
private:
    void reset_pos(bool is_animate);
private:
    const QLineF m_line;
    QGraphicsScene* m_scene;
    std::map<Card, Card_Item*> m_map;
};

#endif // ITEM_RECT_H
