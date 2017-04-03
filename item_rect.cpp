#include "item_rect.h"

Item_Rect::Item_Rect(const QLineF &rect, QGraphicsScene* scene)
    :m_line(rect)
    ,m_scene(scene)
{

}

bool Item_Rect::contains(const Card &c) const
{
    return m_map.find(c)!=m_map.cend();
}

bool Item_Rect::add(const Card &c, Card_Item *item)
{
    bool b = m_map.insert({c, item}).second;
    if (b)
        reset_pos(true);
    return b;
}

Card_Item *Item_Rect::remove(const Card &c)
{
    auto p = m_map.find(c);
    if (p==m_map.cend())
        return 0;

    Card_Item *item = p->second;
    m_map.erase(p);
    reset_pos(true);
    return item;
}

std::set<Card> Item_Rect::get_cards() const
{
    std::set<Card> s;
    for (auto p : m_map)
    {
        s.insert(p.first);
    }
    return s;
}

Card_Item *Item_Rect::init(const Card &c, bool is_animate)
{
    if (contains(c))
        return 0;

    Card_Item* item = Card_Item::from_card(c);
    m_scene->addItem(item);
    m_map.insert({c, item});
    reset_pos(is_animate);
    return item;
}

void Item_Rect::reset_pos(bool is_animate)
{
    int size = m_map.size();
    if (size == 0)
        return;

    QPointF step(m_line.dx(), m_line.dy());
    if (size>=3)
        step /= (size-1);
    QPointF start = m_line.p1();

    for (auto iter=m_map.crbegin(); iter!=m_map.crend(); ++iter)
    {
        Card_Item* item = iter->second;
        if (is_animate)
            item->animate_move(start);
        else
            item->setPos(start);
        start+=step;
    }
}
