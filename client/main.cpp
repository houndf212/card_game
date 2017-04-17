#include <QApplication>
#include "static_deck.h"
#include "static_cardimage.h"
#include "comparehandinfowidget.h"
#include "hostandport.h"
#include <unordered_map>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Static_Deck::init();
    Static_CardImage::init_image();

    CompareHandInfoWidget w;
    w.show();
    std::unordered_map<HostAndPort, QString> m;

    return a.exec();
}
