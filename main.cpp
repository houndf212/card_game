#include "widget.h"
#include <QtWidgets>
#include <QApplication>
#include "image_deck.h"
#include "card_deck.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Image_Deck::init_image();
    Card_Deck deck;
    deck.shuffle();

    QHBoxLayout *layout = new QHBoxLayout;
    for (int i=0; i<4; ++i)
    {
        Card card = deck.get_card(i);
        QPixmap pixmap = Image_Deck::get_image(card);
        QLabel *l = new QLabel;
        l->setPixmap(pixmap);
        layout->addWidget(l);
    }
    QWidget w;
    w.setLayout(layout);
    w.show();
    return a.exec();
}
