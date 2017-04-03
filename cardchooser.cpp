#include "cardchooser.h"
#include "static_deck.h"
#include "static_cardimage.h"
#include "hand_info.h"

CardChooser::CardChooser(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene (new QGraphicsScene(0, 0, 840, 800, this))
    ,m_spade_rect({10, 10, 600, 10}, m_scene)
    ,m_heart_rect({10, 165, 600, 165}, m_scene)
    ,m_club_rect({10, 320, 600, 320}, m_scene)
    ,m_diamond_rect({10, 475, 600, 475}, m_scene)
    ,m_joker_rect({720, 200, 720, 400}, m_scene)
    ,m_selected_rect({10, 630, 700, 630}, m_scene)
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setScene(m_scene);
//    this->resize(860, 810);
    init_card();
}

std::set<Card> CardChooser::selected_cards() const
{
    return m_selected_rect.get_cards();
}

void CardChooser::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    { clean_seleceted(); }
    QGraphicsView::mousePressEvent(event);
}

void CardChooser::onCardClicked()
{
    Card_Item* item = dynamic_cast<Card_Item*>(sender());
    Q_ASSERT(item!=0);
    Card card = item->card();
    if (m_selected_rect.contains(card))
    {
        unselect(card);
    }
    else
    {
        selecet(card);
    }

    Q_EMIT sig_slected();
}

void CardChooser::init_card()
{
    for (int i=0; i<52; )
    {
        m_diamond_rect.init(Static_Deck::index_card(i++), false);
        m_club_rect.init(Static_Deck::index_card(i++), false);
        m_heart_rect.init(Static_Deck::index_card(i++), false);
        m_spade_rect.init(Static_Deck::index_card(i++), false);
    }

    m_joker_rect.init(Static_Deck::index_card(52), false);
    m_joker_rect.init(Static_Deck::index_card(53), false);

    init_to_all_item();
}

void CardChooser::init_to_all_item()
{
    for (QGraphicsItem* item : m_scene->items())
    {
         Card_Item *card = dynamic_cast<Card_Item*>(item);
         if (card!=0)
         {
             connect(card, &Card_Item::sig_clicked, this, &CardChooser::onCardClicked);
         }
    }
}

void CardChooser::clean_seleceted()
{
    for (auto c : selected_cards())
    {
        unselect(c);
    }
    Q_EMIT sig_slected();
}

void CardChooser::selecet(const Card &c)
{
    Item_Rect *rect = belongto(c);
    m_selected_rect.add(c, rect->remove(c));
}

void CardChooser::unselect(const Card &c)
{
    Item_Rect *rect = belongto(c);
    rect->add(c, m_selected_rect.remove(c));
}

Item_Rect *CardChooser::belongto(const Card &c)
{
    switch (c.color())
    {
    case Card::diamond:
        return &m_diamond_rect;
    case Card::club:
        return &m_club_rect;
    case Card::heart:
        return &m_heart_rect;
    case Card::spade:
        return &m_spade_rect;
    case Card::black_joker:
    case Card::red_joker:
        return &m_joker_rect;
    default:
        Q_ASSERT(false);
        break;
    }
    return 0;
    Q_ASSERT(false);
}
