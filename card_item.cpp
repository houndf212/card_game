#include "card_item.h"
#include "static_deck.h"
#include "static_cardimage.h"
#include <QGraphicsSceneMouseEvent>

Card_Item::Card_Item(QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
//    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformationMode(Qt::SmoothTransformation);

    m_animation = new QPropertyAnimation(this, "pos", this);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
}

void Card_Item::setCard(const Card &card)
{
    m_card = card;
    QPixmap pixmap = Static_CardImage::get_image(m_card);
    setPixmap(pixmap);
//    setScale(2);
}

void Card_Item::animate_move(const QPointF &p)
{
    if (pos() == p)
        return;

    m_animation->stop();
    m_animation->setStartValue(pos());
    m_animation->setEndValue(p);
    int msec = calc_time(pos(), p);
    m_animation->setDuration(msec);
    m_animation->start();
}

void Card_Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        Q_EMIT sig_clicked();
}

void Card_Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

}

void Card_Item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{

}

int Card_Item::calc_time(const QPointF &p1, const QPointF &p2)
{
    QLineF line(p1, p2);
    qreal dist = line.dx()*line.dx() + line.dy()*line.dy();
    dist = std::sqrt(dist);

    return std::max<int>(400, dist);
}

Card_Item *Card_Item::from_card(const Card &c)
{
    Card_Item *item = new Card_Item;
    item->setCard(c);
    int index = - Static_Deck::card_index(c);
    item->setZValue(index);
    return item;
}
