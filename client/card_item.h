#ifndef CARD_ITEM_H
#define CARD_ITEM_H
#include <QtCore>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "card.h"

class Card_Item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    static Card_Item* from_card(const Card& c);
    Q_SIGNAL void sig_clicked();
    Card card() const { return m_card; }
    void animate_move(const QPointF& p);
private:
    Card_Item(QGraphicsItem* parent=0);
    void setCard(const Card& card);
protected:
    // The mouse press event decides which item should become the mouse grabber (see QGraphicsScene::mouseGrabberItem()).
    // If you do not reimplement this function, the press event will propagate to any topmost item beneath this item,
    // and no other mouse events will be delivered to this item.
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
private:
    static int calc_time(const QPointF& p1, const QPointF& p2);
private:
    Card m_card;
    QPropertyAnimation* m_animation;
};

#endif // CARD_ITEM_H
