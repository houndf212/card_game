#include <QApplication>
#include "static_deck.h"
#include "static_cardimage.h"
#include "comparehandinfowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Static_Deck::init();
    Static_CardImage::init_image();

    CompareHandInfoWidget w;
    w.show();

    return a.exec();
}
