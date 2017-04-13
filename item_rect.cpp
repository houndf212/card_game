#include "item_rect.h"
#include "static_cardimage.h"

Item_Rect::Item_Rect(const QLineF &rect, QGraphicsScene* scene)
    :m_line(rect)
    ,m_scene(scene)
{

}

bool Item_Rect::contains(const Card &c) const
{
    return m_map.find(c)!=m_map.cend();
}

void Item_Rect::hint(const CardList &cards)
{
    reset_pos(false);
    for(const Card& c : cards)
    {
        Q_ASSERT(contains(c));
        Card_Item* item = m_map[c];
        QPointF p = item->pos();
        p.ry() -= 20;
        item->animate_move(p);
    }
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
    std::map<Card, Card_Item*>::const_iterator p = m_map.find(c);
    if (p==m_map.cend())
        return 0;

    Card_Item *item = p->second;
    m_map.erase(p);
    reset_pos(true);
    return item;
}

CardList Item_Rect::get_cards() const
{
    CardList s;
    for (const std::map<Card, Card_Item*>::value_type& p : m_map)
    {
        s.push_back(p.first);
    }
    return s;
}

Card_Item *Item_Rect::init(const Card &c)
{
    if (contains(c))
        return 0;

    Card_Item* item = Card_Item::from_card(c);
    m_scene->addItem(item);
    m_map.insert({c, item});
    reset_pos(false);
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

    step.rx() = std::min<qreal>(step.x(), Static_CardImage::image_size().width());
    step.ry() = std::min<qreal>(step.y(), Static_CardImage::image_size().height());
    QPointF start = m_line.p1();

    for (std::map<Card, Card_Item*>::const_reverse_iterator iter=m_map.crbegin();
         iter!=m_map.crend();
         ++iter, start+=step)
    {
        Card_Item* item = iter->second;
        if (is_animate)
            item->animate_move(start);
        else
            item->setPos(start);
    }
}
