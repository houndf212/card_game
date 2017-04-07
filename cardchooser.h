#ifndef CARDCHOOSER_H
#define CARDCHOOSER_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "item_rect.h"
#include "handinfowidget.h"

class CardChooser : public QGraphicsView
{
    Q_OBJECT
public:
    CardChooser(QWidget *parent = 0);
    Q_SIGNAL void sig_slected();
    CardList selected_cards() const;
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
private:
    Q_SLOT void onCardClicked();
private:
    void init_card();
    void init_to_all_item();
    void clean_seleceted();

    void selecet(const Card& c);
    void unselect(const Card& c);
    Item_Rect* belongto(const Card& c);
private:
    QGraphicsScene* m_scene;

    Item_Rect m_spade_rect;
    Item_Rect m_heart_rect;
    Item_Rect m_club_rect;
    Item_Rect m_diamond_rect;

    Item_Rect m_joker_rect;

    Item_Rect m_selected_rect;
};

#endif // CARDCHOOSER_H
